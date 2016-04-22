#include "StaticLight.h"

typedef Position Pos;

ReferenceFrame StaticLight::GetRefFrameAtTime(double) const
{
	return ReferenceFrame::Default;
}
Position StaticLight::GetPositionAtTime(double time) const
{
	return Pos(Position, time);
}
Spectrum StaticLight::GetSpectrumAtTime(double) const
{
	return GetSpectrum();
}
bool StaticLight::IsStatic() const
{
	return true;
}

StaticLight::StaticLight(const Vector3d& pos) :
	Position(pos)
{

}
