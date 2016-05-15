#pragma once

#include "ObjectBase.h"

class InfiniteCylinderY : public ObjectBase
{
public:
	ColourSourcePtr Colour;
	ReferenceFrame RefFrame;
	Vector4d InitialPosition;
	double Radius;

	virtual IntersectionList AllIntersections(const Ray& ray) const override final;
	virtual bool AnyIntersections(const Ray& ray) const override final;

	InfiniteCylinderY() = default;
};
