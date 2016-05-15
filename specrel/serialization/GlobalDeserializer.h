#pragma once

#include "..\Deserializer.h"

class GlobalDeserializer : public Deserializer
{
public:
	bool DeserializeToFrame(FramePtr frame, const TypeInfo& info, std::ostream& log);
};
