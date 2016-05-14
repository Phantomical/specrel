#pragma once

#include "PreDefs.h"

#include <map>
#include <iosfwd>

struct Value
{
	enum
	{
		NUMBER,
		VEC2,
		VEC3,
		VEC4,
		STRING
	} Type;
	union
	{
		double Number;
		Vector2d Vec2;
		Vector3d Vec3;
		Vector4d Vec4;
		const char* StrVal;
	};

	Value(double num = 0.0) :
		Type(NUMBER),
		Number(num)
	{

	}
	Value(const Vector2d& vec) :
		Type(VEC2),
		Vec2(vec)
	{

	}
	Value(const Vector3d& vec) :
		Type(VEC3),
		Vec3(vec)
	{

	}
	Value(const Vector4d& vec) :
		Type(VEC4),
		Vec4(vec)
	{

	}
	Value(const char* str) :
		Type(STRING),
		StrVal(str)
	{

	}
};
struct TypeInfo
{
	std::string TypeName;                // The name of the type
	std::map<std::string, Value> Values; // The values of the type
};

class Deserializer
{
public:
	virtual void DeserializeToScene(FramePtr frame, const TypeInfo& info, std::ostream& log) = 0;
	virtual ~Deserializer() = default;

	static std::shared_ptr<Deserializer> GetDeserializer(const std::string& type);
};

typedef std::shared_ptr<Deserializer> DeserializerPtr;
