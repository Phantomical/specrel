#pragma once

#include "ObjectBase.h"

class StaticSphere : public ObjectBase
{
public:
	Vector3d Pos;
	double Radius;
	ColourSourcePtr Source;
	
	virtual Position GetPosition(double time) const override final;
	virtual ReferenceFrame GetReferenceFrame(double time) const override final;
	virtual IntersectionList Intersect(const Ray& ray) const override final;

	StaticSphere() = default;
	StaticSphere(const Vector3d& pos, double radius, ColourSourcePtr source);
};
