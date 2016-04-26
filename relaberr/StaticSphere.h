#pragma once

#include "ObjectBase.h"

class StaticSphere : public ObjectBase
{
public:
	Position Pos;
	double Radius;
	
	virtual Position GetPosition(double time) const override final;
	virtual ReferenceFrame GetReferenceFrame(double time) const override final;
	virtual IntersectionList Intersect(const Ray& ray) const override final;
};
