#include "core\scene.h"

ReferenceFrame LightBase::GetRefFrame() const
{
	return LightTransform.RefFrame;
}
Transform LightBase::GetTransform() const
{
	return LightTransform;
}
