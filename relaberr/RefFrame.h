#ifndef SPECREL_REFFRAME_H
#define SPECREL_REFFRAME_H

#include "PreDefs.h"
#include "Velocity.h"
#include "Position.h"
#include "Matrix.h"

struct ReferenceFrame
{
	ReferenceFrame() = default;
	ReferenceFrame(const Velocity& vel);

	Velocity Velocity; // The velocity of this reference frame

	static const ReferenceFrame Default;
};

Matrix44d BoostMatrix(const ReferenceFrame& old, const ReferenceFrame& new_);
Matrix44d BoostMatrix(const Velocity& v);

Position TransformPosition(const Position&, const ReferenceFrame& old, const ReferenceFrame& new_);
Velocity TransformVelocity(const Velocity&, const ReferenceFrame& old, const ReferenceFrame& new_);

#endif
