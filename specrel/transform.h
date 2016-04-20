#ifndef SPECREL_TRANSFORM_H
#define SPECREL_TRANSFORM_H

#include "quat.h"
#include "RefFrame.h"

struct Transform
{
	ReferenceFrame RefFrame; // The reference frame of this point in spacetime
	Vector4d Position;       // Spacetime coordinates of this point
	Quaterniond Rotation;    // Rotation of this point

	//Transforms this point to another frame of reference
	Transform ToReferenceFrame(ReferenceFrame new_frame) const;
	//Transforms this point to the global frame of reference
	Transform ToGlobalFrame() const;

	//Takes a velocity in this reference frame and transforms it to new_frame
	Vector3d VelToReferenceFrame(const Vector3d& vel, ReferenceFrame new_frame) const;
	//Takes a velocity in this reference frame and transforms it to the default reference frame
	Vector3d VelToGlobalFrame(const Vector3d& vel) const;

	Transform() = default;
	Transform(const Vector4d& pos);
	Transform(const Vector4d& pos, const Quaterniond& rot);
	Transform(const Vector4d& pos, const Quaterniond& rot, const ReferenceFrame& ref_frame);
};

#endif
