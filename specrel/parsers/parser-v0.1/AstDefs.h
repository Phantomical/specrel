#pragma once

#include <string>
#include <vector>
#include "AST.h"

void DeleteNode(TypeNode*);
void DeleteNode(ProgramNode*);
void DeleteNode(VectorNode*);

struct ValueNodeImpl
{
	enum
	{
		DOUBLE,
		INT,
		STRING
	} type;

	union
	{
		double dval;
		int ival;
		const char* sval;
	};

	ValueNodeImpl(double val) :
		type(DOUBLE),
		dval(val)
	{

	}
	ValueNodeImpl(int val) :
		type(INT),
		ival(val)
	{

	}
	ValueNodeImpl(const char* val) :
		type(STRING),
		sval(val)
	{

	}
};
struct ColourNode
{
	ValueNode* Identifier;
	VectorNode* Value;

	ColourNode(ValueNode* iden, VectorNode* val) :
		Identifier(iden),
		Value(val)
	{

	}
	~ColourNode()
	{
		delete Identifier;
		DeleteNode(Value);
	}
};
struct UnitValueNode
{
	ValueNode* Number;
	ValueNode* Unit;

	UnitValueNode(ValueNode* num, ValueNode* unit) :
		Number(num),
		Unit(unit)
	{

	}
	~UnitValueNode()
	{
		delete Number;
		delete Unit;
	}
};

struct AssignNodeImpl
{
	ValueNode* Identifier;
	ExpressionNode* Expr;

	AssignNodeImpl(ValueNode* iden, ExpressionNode* expr) :
		Identifier(iden),
		Expr(expr)
	{

	}
};
struct ExpressionNodeImpl
{
	enum
	{
		COLOUR,
		UNIT_VALUE,
		VECTOR,
		VALUE
	} Type;

	union
	{
		ColourNode* Colour;
		UnitValueNode* UnitVal;
		VectorNode* Vector;
		ValueNode* Value;
	};

	ExpressionNodeImpl(ColourNode* c) :
		Type(COLOUR),
		Colour(c)
	{

	}
	ExpressionNodeImpl(UnitValueNode* UnitVal) :
		Type(UNIT_VALUE),
		UnitVal(UnitVal)
	{

	}
	ExpressionNodeImpl(VectorNode* vec) :
		Type(VECTOR),
		Vector(vec)
	{

	}
	ExpressionNodeImpl(ValueNode* val) :
		Type(VALUE),
		Value(val)
	{

	}

	~ExpressionNodeImpl()
	{
		switch (Type)
		{
		case COLOUR:
			delete Colour;
			break;
		case UNIT_VALUE:
			delete UnitVal;
			break;
		case VECTOR:
			DeleteNode(Vector);
			break;
		case VALUE:
			delete Value;
			break;
		}
	}
};

struct TypeNodeImpl
{
	std::vector<AssignNode*> Nodes;
	ValueNode* Identifier;

	TypeNodeImpl() :
		Identifier(nullptr)
	{

	}
	~TypeNodeImpl()
	{
		if (Identifier)
			delete Identifier;
		for (auto n : Nodes)
			delete n;
	}
};
struct ProgramNodeImpl
{
	std::vector<TypeNode*> Types;

	~ProgramNodeImpl()
	{
		for (auto n : Types)
			DeleteNode(n);
	}
};
struct VectorNodeImpl
{
	std::vector<ExpressionNode*> Values;

	~VectorNodeImpl()
	{
		for (auto n : Values)
			delete n;
	}
};

