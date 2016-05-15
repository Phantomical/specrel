#pragma once

#include "..\Deserializer.h"
#include "..\Frame.h"

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


