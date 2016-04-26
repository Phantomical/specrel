#include "StaticPointLight.h"

typedef Position Pos;

ColourSourcePtr StaticPointLight::GetColour() const
{
	return ColourSource;
}

StaticPointLight::StaticPointLight(const Pos& pos, ColourSourcePtr source) :
	StaticLight(subvec<3>(pos)),
	ColourSource(source)
{

}
StaticPointLight::StaticPointLight(const Vector3d& pos, ColourSourcePtr source) :
	StaticLight(pos),
	ColourSource(source)
{

}
