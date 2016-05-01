#pragma once

#include "ObjectBase.h"

class Sphere : public ObjectBase
{
public:
	ColourSourcePtr ColourSource;
	Vector4d InitialPosition;
	ReferenceFrame RefFrame;
	double Radius;

	virtual IntersectionList AllIntersections(const Ray& ray) const override;
	virtual bool AnyIntersections(const Ray& ray) const override;

	Sphere() = default;
	Sphere(const Vector4d& pos, double radius, ColourSourcePtr source, const ReferenceFrame& ref_frame = ReferenceFrame::Default);
};
