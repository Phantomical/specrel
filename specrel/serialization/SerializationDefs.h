#pragma once

#include "..\Deserializer.h"
#include "..\Frame.h"
#include <string>

#define DESERIALIZER_CLASS(type, tokenname) class type##Deserializer : public Deserializer \
	{ \
		static const char* const TokenName; \
		static const char* const TypeName; \
	public: \
		bool DeserializeToFrame(FramePtr, const TypeInfo& info, std::ostream& log); \
	}; \
	const char* const type##Deserializer::TokenName = tokenname; \
	const char* const type##Deserializer::TypeName = #type "Deserializer"
#define DESERIALIZER_FACTORY_FUNC(type) \
	DeserializerPtr type##DeserializerFactoryFunc() \
	{ \
		return DeserializerPtr(new type##Deserializer); \
	}
#define DESERIALIZER_REGISTRAR(type, tokenname) \
	struct type##DeserializerFactory \
	{ \
		type##DeserializerFactory() \
		{ \
			Deserializer::RegisterDeserializer(tokenname, &type##DeserializerFactoryFunc); \
		} \
	}; \
	static type##DeserializerFactory type##DeserializerFactoryInstance = type##DeserializerFactory()

#define DESERIALIZER_DEFS(type, tokenname) \
	DESERIALIZER_CLASS(type, tokenname); \
	DESERIALIZER_FACTORY_FUNC(type); \
	DESERIALIZER_REGISTRAR(type, tokenname)

namespace detail
{
	template<Value::TypeName eType>
	struct ValueAccessor;

	template<> struct ValueAccessor<Value::STRING>
	{
		static std::string GetValue(const Value& v)
		{
			return v.StrVal;
		}
	};
	template<> struct ValueAccessor<Value::NUMBER>
	{
		static double GetValue(const Value& v)
		{
			return v.Number;
		}
	};
	template<> struct ValueAccessor<Value::VEC2>
	{
		static Vector2d GetValue(const Value& v)
		{
			return v.Vec2;
		}
	};
	template<> struct ValueAccessor<Value::VEC3>
	{
		static Vector3d GetValue(const Value& v)
		{
			return v.Vec3;
		}
	};
	template<> struct ValueAccessor<Value::VEC4>
	{
		static Vector4d GetValue(const Value& v)
		{
			return v.Vec4;
		}
	};

	template<typename vTy> struct GetValueType;
	template<> struct GetValueType<std::string> { static constexpr Value::TypeName value = Value::STRING; };
	template<> struct GetValueType<double> { static constexpr Value::TypeName value = Value::NUMBER; };
	template<> struct GetValueType<Vector2d> { static constexpr Value::TypeName value = Value::VEC2; };
	template<> struct GetValueType<Vector3d> { static constexpr Value::TypeName value = Value::VEC3; };
	template<> struct GetValueType<Vector4d> { static constexpr Value::TypeName value = Value::VEC4; };

	template<typename vTy>
	struct UnrefImpl
	{
		typedef vTy type;
	};
	template<typename vTy>
	struct UnrefImpl<vTy&>
	{
		typedef typename UnrefImpl<vTy>::type type;
	};
	template<typename vTy>
	struct UnrefImpl<const vTy>
	{
		typedef typename UnrefImpl<vTy>::type type;
	};
	template<typename vTy>
	struct UnrefImpl<vTy&&>
	{
		typedef typename UnrefImpl<vTy>::type type;
	};

	template<typename vTy>
	using Unref = typename UnrefImpl<vTy>::type;

}

enum SetErrorCode
{
	OK = 0,
	NOT_FOUND = 1,
	WRONG_TYPE = 2
};

#define DECL_FUNC(MemberName, TypeName) \
	template<typename vType> \
	SetErrorCode Set_##MemberName(vType* typeinst, const TypeInfo& info) \
	{ \
		auto it = info.Values.find(TypeName); \
		if (it == info.Values.end()) \
			return NOT_FOUND; \
		if (it->second.Type != detail::GetValueType<detail::Unref<decltype(typeinst->MemberName)>>::value) \
			return WRONG_TYPE; \
		typeinst->MemberName = detail::ValueAccessor<detail::GetValueType<detail::Unref<decltype(typeinst->MemberName)>>::value>::GetValue(it->second); \
		return OK; \
	}
#define DESERIALIZE(MemberName, TypeName, typeinst, info, log, errorbit)\
	[&](){ \
		auto it = info.Values.find(TypeName); \
		if (it == info.Values.end()) \
		{ \
			log << "[ERROR] \"" << TypeName << "\" was not found in type \"" << TokenName << "\"." << std::endl; \
			errorbit = true; \
		} \
		if (it->second.Type != detail::GetValueType<detail::Unref<decltype(typeinst->MemberName)>>::value) \
		{ \
			log << "[ERROR] \"" << TypeName << "\" in type \"" << TokenName << "\" was not of correct type." << std::endl;\
		} \
		typeinst->MemberName = detail::ValueAccessor<detail::GetValueType<detail::Unref<decltype(typeinst->MemberName)>>::value>::GetValue(it->second); \
	}()



