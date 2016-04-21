#ifndef SPECREL_REFFRAME_H
#define SPECREL_REFFRAME_H

#include "PreDefs.h"
#include "Velocity.h"
#include "Position.h"

struct ReferenceFrame
{
	ReferenceFrame() = default;
	ReferenceFrame(const Velocity& vel);

	Velocity Velocity; // The velocity of this reference frame

	static const ReferenceFrame Default;
};

Position TransformPosition(const Position&, const ReferenceFrame& old, const ReferenceFrame& new_);
Velocity TransformVelocity(const Velocity&, const ReferenceFrame& old, const ReferenceFrame& new_);

#endif
