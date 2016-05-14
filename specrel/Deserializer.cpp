#include "Deserializer.h"

DeserializerPtr Deserializer::GetDeserializer(const std::string& type)
{
	printf("GetDeserializer() called with type: %s\n", type.c_str());

	return nullptr;
}
