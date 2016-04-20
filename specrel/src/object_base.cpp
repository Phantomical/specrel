#include "core/scene.h"

Medium ObjectBase::GetInternalMedium() const
{
	return InternalMedium;
}
ReferenceFrame ObjectBase::GetRefFrame() const
{
	return RefFrame;
}
bool ObjectBase::IsTransparent() const
{
	return Transparent;
}
