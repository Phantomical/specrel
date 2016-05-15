#pragma once

#include "..\Deserializer.h"

class SphereDeserializer : public Deserializer
{
public:
	virtual bool DeserializeToFrame(FramePtr, const TypeInfo&, std::ostream& log) override final;
};
