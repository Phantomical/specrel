#pragma once

#include "..\Deserializer.h"

class DirectionalLightDeserializer : public Deserializer
{
public:
	bool DeserializeToFrame(FramePtr, const TypeInfo& info, std::ostream& log);
};
