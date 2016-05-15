#pragma once

#include "..\Deserializer.h"

class AmbientLightDeserializer : public Deserializer
{
public:
	bool DeserializeToFrame(FramePtr, const TypeInfo&, std::ostream&);
};
