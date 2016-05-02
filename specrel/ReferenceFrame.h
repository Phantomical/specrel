#pragma once

#include "PreDefs.h"

struct ReferenceFrame
{
	Vector3d Velocity;

	double Gamma() const;

	ReferenceFrame() = default;
	ReferenceFrame(const Vector3d& vel);

	static const ReferenceFrame Default;
};

ReferenceFrame operator +(const ReferenceFrame&);
ReferenceFrame operator -(const ReferenceFrame&);

ReferenceFrame operator +(const ReferenceFrame&, const ReferenceFrame&);
ReferenceFrame operator -(const ReferenceFrame&, const ReferenceFrame&);

Vector4d LorentzTransform(const Vector4d& position, const ReferenceFrame& start, const ReferenceFrame& old);
Vector3d LorentzTransform(const Vector3d& velocity, const ReferenceFrame& start, const ReferenceFrame& old);
Vector3d TransformDir(const Vector3d& direction, const ReferenceFrame& start, const ReferenceFrame& end);
