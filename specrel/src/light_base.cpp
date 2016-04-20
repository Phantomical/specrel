#include "core\light_base.h"

ReferenceFrame LightBase::GetRefFrame() const
{
	return LightTransform.RefFrame;
}
Transform LightBase::GetTransform() const
{
	return LightTransform;
}
ObjectBasePtr LightBase::GetLightVolume() const
{
	return LightVolume;
}
