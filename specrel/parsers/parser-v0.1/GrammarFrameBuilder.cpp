#include "GrammarFrameBuilder.h"

#include "..\..\Frame.h"
#include "..\..\Deserializer.h"

#include <cstdlib>
#include <iostream>
#include <cassert>

#ifndef TRACE
#	define NDEBUG
#endif

#include "lexer.h"
#include "AstDefs.h"

extern "C"
{
#include "parser.h"
}

#ifdef _MSC_VER
#	pragma warning(disable:4706)
#endif

#define ParseAlloc Parser_v0_1_Alloc
#define ParseFree Parser_v0_1_Free
#define ParseTrace Parser_v0_1_Trace
#define Parse Parser_v0_1_

namespace grammar_v0_1
{
	using std::exception;

	std::ostream& operator <<(std::ostream& os, decltype(Value::Type) type)
	{
		switch (type)
		{
		case Value::NUMBER:
			os << "number";
		case Value::STRING:
			os << "string";
		case Value::VEC2:
			os << "vec2";
		case Value::VEC3:
			os << "vec3";
		case Value::VEC4:
			os << "vec4";
		}
		return os;
	}

	struct Evaluator
	{
		std::ostream& log;
		bool errorbit;

		Evaluator(std::ostream& os) :
			log(os),
			errorbit(false)
		{

		}

		Value EvaluateExpression(ValueNode* val)
		{
			switch (val->type)
			{
			case ValueNode::DOUBLE:
				return Value(val->dval);
			case ValueNode::INT:
				return Value((double)val->ival / 255.0);
			case ValueNode::STRING:
				return Value(val->sval);
			}
			log << "[ERROR] Unkown value type found." << std::endl;
			errorbit = true;
			return Value(0.0);
		}
		Value EvaluateExpression(VectorNode* vec)
		{
			size_t sz = vec->Impl->Values.size();

			if (sz == 0)
			{
				log << "[ERROR] Empty vector found." << std::endl;
				errorbit = true;
				return Value(0.0);
			}
			if (sz == 1)
			{
				return EvaluateExpression(vec->Impl->Values[0]);
			}
			if (sz == 2)
			{
				Value v1 = EvaluateExpression(vec->Impl->Values[0]);
				Value v2 = EvaluateExpression(vec->Impl->Values[1]);

				if (v1.Type != v2.Type)
				{
					log << "[ERROR] Vector elements of different types: "
						<< v1.Type << " and " << v2.Type << std::endl;
					errorbit = true;
					return Value(Vector2d::zero());
				}

				if (v1.Type != Value::NUMBER)
				{
					log << "[ERROR] Vector elements were of type: " << v1.Type
						<< ". Expected " << Value::NUMBER << std::endl;
					errorbit = true;
					return Value(Vector2d::zero());
				}

				return Value(Vector2d(v1.Number, v2.Number));
			}
			if (sz == 3)
			{
				Value v1 = EvaluateExpression(vec->Impl->Values[0]);
				Value v2 = EvaluateExpression(vec->Impl->Values[1]);
				Value v3 = EvaluateExpression(vec->Impl->Values[2]);

				if (v1.Type != v2.Type || v1.Type != v3.Type)
				{
					log << "[ERROR] Vector elements of different types: " << v1.Type
						<< ", " << v2.Type << " and " << v3.Type << "." << std::endl;
					errorbit = true;
					return Value(Vector3d::zero());
				}

				if (v1.Type != Value::NUMBER)
				{
					log << "[ERROR] Vector elements were of type: " << v1.Type
						<< ". Expected " << Value::NUMBER << "." << std::endl;
					errorbit = true;
					return Value(Vector3d::zero());
				}

				return Value(Vector3d(v1.Number, v2.Number, v3.Number));
			}
			if (sz > 4)
			{
				log << "[WARNING] Vector of size greater than 4 truncated to 4 elements."
					<< std::endl;
			}

			Value v1 = EvaluateExpression(vec->Impl->Values[0]);
			Value v2 = EvaluateExpression(vec->Impl->Values[1]);
			Value v3 = EvaluateExpression(vec->Impl->Values[2]);
			Value v4 = EvaluateExpression(vec->Impl->Values[3]);

			if (v1.Type != v2.Type || v1.Type != v2.Type || v1.Type != v3.Type)
			{
				log << "[ERROR] Vector elements of different types: "
					<< v1.Type << ", " << v2.Type << ", " << v3.Type
					<< " and " << v4.Type << "." << std::endl;
				errorbit = true;
				return Value(Vector4d::zero());
			}

			if (v1.Type != Value::NUMBER)
			{
				log << "[ERROR] Vector elements were of type: " << v1.Type
					<< ". Expected " << Value::NUMBER << "." << std::endl;
				errorbit = true;
				return Value(Vector4d::zero());
			}

			return Value(Vector4d(v1.Number, v2.Number, v3.Number, v4.Number));
		}
		Value EvaluateExpression(ColourNode* colour)
		{
			if (colour->Identifier->type != ValueNode::STRING)
			{
				log << "[ERROR] Invalid colour declaration found." << std::endl;
				errorbit = true;
				return Value(0.0);
			}

			if (std::string(colour->Identifier->sval) != "rgb")
			{
				log << "[ERROR] Non-RGB colours are not supported." << std::endl;
				errorbit = true;
				return Value(0.0);
			}

			Value val = EvaluateExpression(colour->Value);
			if (val.Type != Value::VEC3)
			{
				log << "[ERROR] Colour vector had incorrect number of elements." << std::endl;
				errorbit = true;
			}

			return val;
		}
		Value EvaluateExpression(ExpressionNode* expr)
		{
			switch (expr->Type)
			{
			case ExpressionNode::COLOUR:
				return EvaluateExpression(expr->Colour);
			case ExpressionNode::VALUE:
				return EvaluateExpression(expr->Value);
			case ExpressionNode::UNIT_VALUE:
				return Value(EvaluateExpression(expr->UnitVal));
			case ExpressionNode::VECTOR:
				return EvaluateExpression(expr->Vector);
			default:
				log << "[ERROR] Invalid token type encountered." << std::endl;
				errorbit = true;
				return Value(0.0);
			}
		}
		double EvaluateExpression(UnitValueNode* val)
		{
			if (val->Unit->type != ValueNode::STRING)
			{
				log << "[ERROR] Unit was not a valid unit." << std::endl;
				errorbit = true;
				return 0.0;
			}

			Value res = EvaluateExpression(val->Number);
			auto str = std::string(val->Unit->sval);

			if (str == "deg" || str == "degrees")
			{
				if (res.Type != Value::NUMBER)
				{
					log << "[ERROR] Unit value was not a number." << std::endl;
					errorbit = true;
					return 0.0;
				}

				return res.Number * 0.017453292519943295769;
			}
			if (str == "rad")
			{
				return res.Number;
			}

			log << "[WARNING] Units other than radians and degrees are not supported." << std::endl;

			return res.Number;

		}
	};

	void GrammarFrameBuilder::Initialize(const std::string& file)
	{
		ProgramNode* ast = nullptr;

		{
			Lexer lexer = Lexer(file);
			void* parser = ParseAlloc(malloc);
#ifdef TRACE
			ParseTrace(stdout, "[LEXER] ");
#endif

			int token;

			while (token = lexer.NextToken())
			{
				ValueNode* value = nullptr;
				switch (token)
				{
				case TOKEN_HEXVAL:
					value = new ValueNode(std::stoi(lexer.TokenText(), nullptr, 0));
					break;
				case TOKEN_NUMBER:
					value = new ValueNode(std::stod(lexer.TokenText()));
					break;
				case TOKEN_IDENTIFIER:
				{
					auto str = lexer.TokenText();
					auto sz = lexer.TokenSize();
					char* strbuf = new char[sz + 1];
					std::char_traits<char>::copy(strbuf, str, sz);
					strbuf[sz] = '\0';
					Strings.push_back(strbuf);
					value = new ValueNode(strbuf);
					break;
				}
				case 0xFF:
					OutputLog << "[WARNING] Unexpected token found: " << lexer.TokenText() << std::endl;
					break;
				}

				Parse(parser, token, value, &ast);
			}

			Parse(parser, token, nullptr, &ast);

			ParseFree(parser, free);
		}

		if (ast == nullptr)
		{
			OutputLog << "[ERROR] Abstract syntax tree construction failed." << std::endl;

			for (auto str : Strings)
			{
				if (str)
					delete[] str;
			}
			Strings.clear();

			throw ParseErrorException("Abstract syntax tree construction failed.");
		}

		Evaluator Eval(OutputLog);

		for (auto type : ast->Impl->Types)
		{
			TypeInfo info;
			if (type->Impl->Identifier->type == ValueNodeImpl::STRING)
				info.TypeName = type->Impl->Identifier->sval;
			else
			{
				OutputLog << "[ERROR] Type name was an invalid type."
					" Expecting an identifier, found a number instead." << std::endl;
			}


			for (auto assign : type->Impl->Nodes)
			{
				if (assign->Identifier->type == ValueNodeImpl::STRING)
				{
					info.Values[assign->Identifier->sval] = Eval.EvaluateExpression(assign->Expr);
				}
				else
				{
					OutputLog << "[ERROR] Value name in type: " << info.TypeName << " was an invalid type."
						" Expecting an identifier, found a number instead." << std::endl;
				}
			}

			Types.push_back(info);
		}

		DeleteNode(ast);

		if (Eval.errorbit)
		{
			throw ParseErrorException("Parse errored. See output log for details.");
		}
	}
	void GrammarFrameBuilder::FillFrame(FramePtr frame)
	{
		frame->Scene = MakePtr<Scene>();

		bool errorbit = false;

		for (const auto& info : Types)
		{
			DeserializerPtr deserializer = Deserializer::GetDeserializer(info.TypeName);

			if (!deserializer)
			{
				OutputLog << "[WARNING] Unknown type \"" << info.TypeName
					<< "\" found. Type will be ignored." << std::endl;
			}
			else
			{
				if (!deserializer->DeserializeToFrame(frame, info, OutputLog))
					errorbit = true;
			}
		}

		if (errorbit)
			throw ParseErrorException("An error occured while constructing types");
	}
	void GrammarFrameBuilder::FillFrames(std::vector<FramePtr>& frames)
	{
		FramePtr frame = MakePtr<Frame>();

		FillFrame(frame);

		frames.push_back(frame);
	}

	const std::ostream& GrammarFrameBuilder::GetOutputLog() const
	{
		return OutputLog;
	}

	GrammarFrameBuilder::GrammarFrameBuilder() :
		OutputLog(std::cout)
	{

	}
	GrammarFrameBuilder::GrammarFrameBuilder(std::ostream& os) :
		OutputLog(os)
	{

	}
	GrammarFrameBuilder::GrammarFrameBuilder(std::ostream& os, const std::string& filetext) :
		OutputLog(os)
	{
		Initialize(filetext);
	}
	GrammarFrameBuilder::~GrammarFrameBuilder()
	{
		for (auto str : Strings)
			delete[] str;
	}

	FrameBuilderPtr CreateFrameBuilder(std::ostream& os)
	{
		return FrameBuilderPtr(new GrammarFrameBuilder(os));
	}
}
