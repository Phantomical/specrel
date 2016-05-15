#pragma once

#include "..\Deserializer.h"

class CameraDeserializer : public Deserializer
{
public:
	virtual bool DeserializeToFrame(FramePtr, const TypeInfo&, std::ostream&) override final;
};
