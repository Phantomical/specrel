#include "Transform.h"

Transform::Transform(const Vector4d& pos) :
	RefFrame(ReferenceFrame::Default),
	Position(pos),
	Rotation()
{

}
Transform::Transform(const Vector4d& pos, const Quaterniond& rot) :
	RefFrame(ReferenceFrame::Default),
	Position(pos),
	Rotation(rot)
{

}
Transform::Transform(const Vector4d& pos, const Quaterniond& rot, const ReferenceFrame& ref_frame) :
	RefFrame(ref_frame),
	Position(pos),
	Rotation(rot)
{

}

Transform Transform::ToReferenceFrame(ReferenceFrame new_frame) const
{
	return Transform(TransformPosition(Position, RefFrame, new_frame), Rotation, new_frame);
}
Transform Transform::ToGlobalFrame() const
{
	return ToReferenceFrame(ReferenceFrame::Default);
}

Vector3d Transform::VelToReferenceFrame(const Vector3d& vel, ReferenceFrame new_frame) const
{
	return TransformVelocity(vel, RefFrame, new_frame);
}
Vector3d Transform::VelToGlobalFrame(const Vector3d& vel) const
{
	return VelToReferenceFrame(vel, ReferenceFrame::Default);
}
