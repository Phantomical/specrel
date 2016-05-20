#pragma once

#include "ObjectBase.h"

class Torus : public ObjectBase
{
public:
	ColourSourcePtr Colour;
	ReferenceFrame RefFrame;
	Vector4d InitialPosition;
	double RingRadius;
	double Radius;

	IntersectionList AllIntersections(const Ray& ray) const override final;
};
