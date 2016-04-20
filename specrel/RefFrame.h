#ifndef SPECREL_REF_FRAME_H
#define SPECREL_REF_FRAME_H

#include "vector.h"
#include "PreDefs.h"

struct ReferenceFrame
{
	Vector4d Velocity;

	ReferenceFrame() = default;
	ReferenceFrame(const Vector4d& vel) :
		Velocity(vel)
	{

	}

	//The reference frame with no velocity
	static const ReferenceFrame Default;
};

Vector4d TransformPosition(const Vector4d& pos, const ReferenceFrame& old_frame, const ReferenceFrame& new_frame);
Vector3d TransformVelocity(const Vector3d& vel, const ReferenceFrame& old_frame, const ReferenceFrame& new_frame);
Vector4d TransformVelocity(const Vector4d& vel, const ReferenceFrame& old_frame, const ReferenceFrame& new_frame);

#endif
