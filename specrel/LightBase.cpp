#include "LightBase.h"

LightBase::LightBase(const ReferenceFrame& ref_frame) :
	RefFrame(ref_frame)
{

}

ReferenceFrame LightBase::GetRefFrame() const
{
	return RefFrame;
}
