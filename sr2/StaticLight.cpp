#include "StaticLight.h"

typedef Position Pos;

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
