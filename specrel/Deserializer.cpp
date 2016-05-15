#include "Deserializer.h"
#include "ReferenceFrame.h"
#include "RgbColourSource.h"
#include <iostream>
#include <mutex>

bool Deserializer::GetReferenceFrame(ReferenceFrame& RefFrame, const TypeInfo& info, std::ostream& log)
{
	auto it = info.Values.find("type");
	if (it != info.Values.end())
	{
		RefFrame = ReferenceFrame::Default;

		if (it->second.Type != Value::STRING)
		{
			log << "[ERROR] Type field of " << info.TypeName.c_str()
				<< " object was not a string." << std::endl;
			return false;
		}
		else if (it->second.StrVal == std::string("dynamic"))
		{
			auto vel = info.Values.find("velocity");
			if (vel == info.Values.end())
			{
				log << "[WARNING] Type " << info.TypeName.c_str()
					<< " was dynamic but no velocity was found. Assuming velocity is 0."
					<< std::endl;
			}
			else if (vel->second.Type != Value::VEC3)
			{
				log << "[ERROR] Velocity of type " << info.TypeName.c_str()
					<< " was not a 3-vector." << std::endl;
				return false;
			}
			else
			{
				RefFrame.Velocity = vel->second.Vec3;
			}
		}
		else if (it->second.StrVal != std::string("static"))
		{
			log << "[ERROR] Unknown type value: \"" << it->second.StrVal << "\"." << std::endl;
			return false;
		}
	}
	else
	{
		log << "[WARNING] No type field found. Assuming \"static\" was intended." << std::endl;
	}

	return true;
}
bool Deserializer::GetPosition(Vector4d& pos, bool is_static, const TypeInfo& info, std::ostream& log)
{
	auto it = info.Values.find("position");

	if (is_static)
	{
		if (it->second.Type == Value::VEC3)
		{
			pos = Vector4d(it->second.Vec3, 0.0);
		}
		else if (it->second.Type == Value::VEC4)
		{
			pos = it->second.Vec4;
		}
		else
		{
			log << "[ERROR] Position of type: " << info.TypeName.c_str()
				<< " was an invalid type." << std::endl;
			return false;
		}
	}
	else
	{
		if (it->second.Type == Value::VEC4)
		{
			pos = it->second.Vec4;
		}
		else
		{
			log << "[ERROR] Position of type: " << info.TypeName.c_str()
				<< " was an invalid type." << std::endl;
			return false;
		}
	}

	return true;
}
bool Deserializer::GetColour(ColourSourcePtr& src, const TypeInfo& info, std::ostream& log)
{
	auto it = info.Values.find("colour");

	if (it == info.Values.end())
	{
		it = info.Values.find("color");
		if (it == info.Values.end())
		{
			log << "[ERROR] No colour found in type: " << info.TypeName.c_str() << "." << std::endl;
			return false;
		}
	}
	if (it->second.Type != Value::VEC3)
	{
		log << "[ERROR] Colour value in type: " << info.TypeName.c_str()
			<< " was not a colour." << std::endl;
		return false;
	}

	src = ColourSourcePtr(new RgbColourSource(static_cast<Colour>(it->second.Vec3)));
	return true;
}
bool Deserializer::GetVelocity(Vector3d& vel, const TypeInfo& info, std::ostream& log)
{
	auto it = info.Values.find("velocity");

	if (it == info.Values.end())
	{
		log << "[ERROR] Expected to find a \"velocity\" type in type \""
			<< info.TypeName.c_str() << "\". None found." << std::endl;
		return false;
	}

	if (it->second.Type == Value::VEC3)
	{
		vel = it->second.Vec3;
	}
	else
	{
		log << "[ERROR] Velocity of type: " << info.TypeName.c_str()
			<< " was an invalid type." << std::endl;
		return false;
	}

	return true;
}

bool Deserializer::GetNumber(double& out, const Value& val)
{
	if (val.Type != Value::NUMBER)
		return false;

	out = val.Number;
	return true;
}
bool Deserializer::GetVector(Vector3d& out, const Value& val)
{
	if (val.Type != Value::VEC3)
		return false;

	out = val.Vec3;
	return true;
}
bool Deserializer::GetVector(Vector4d& out, const Value& val)
{
	if (val.Type != Value::VEC4)
		return false;

	out = val.Vec4;
	return true;
}

namespace
{
	struct Container
	{
		std::mutex FactoryFuncsLock;
		std::map<std::string, DeserializerPtr(*)()> FactoryFuncs;
	};

	Container* Factory = nullptr;
}

void Deserializer::RegisterDeserializer(const std::string& type, DeserializerPtr(*factory_func)())
{
	if (!Factory)
		Factory = new Container;

	Factory->FactoryFuncs[type] = factory_func;
}
DeserializerPtr Deserializer::GetDeserializer(const std::string& type)
{
#ifdef TRACE
	printf("[TRACE] GetDeserializer() called with type: \"%s\".\n", type.c_str());
#endif

	if (!Factory)
		Factory = new Container;

	auto it = Factory->FactoryFuncs.find(type);

	if (it != Factory->FactoryFuncs.end())
		return it->second();

	return nullptr;
}
