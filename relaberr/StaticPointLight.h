#pragma once

#include "StaticLight.h"
#include "Position.h"

class StaticPointLight : public StaticLight
{
public:
	ColourSourcePtr ColourSource;

	virtual ColourSourcePtr GetColour() const;

	StaticPointLight(const ::Position& pos, ColourSourcePtr source);
	StaticPointLight(const Vector3d& pos, ColourSourcePtr source);
};
