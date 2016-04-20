#include "RefFrame.h"

const ReferenceFrame ReferenceFrame::Default = ReferenceFrame(Vector4d(0.0, 0.0, 0.0, 1.0));

Vector4d TransformPosition(const Vector4d& pos, const ReferenceFrame& old_frame, const ReferenceFrame& new_frame)
{
	ReferenceFrame relative_frame = ReferenceFrame(new_frame.Velocity - old_frame.Velocity);
	double velocity = relative_frame.Velocity.magnitude();
	Vector4d direction = relative_frame.Velocity * (1.0 / velocity);

	double gamma = 1.0 / std::sqrt(1.0 - velocity * velocity);

	// Parallel part of the vector
	Vector4d prl = dot(pos, direction) * direction;
	// Perpendicular part of the vector
	Vector4d prp = pos - prl;

	// New parallel position component (The perpendicular part isn't changed)
	Vector4d pnew = gamma * (prl - relative_frame.Velocity * pos.t);

	return Vector4d(pnew + prp);
}
Vector3d TransformVelocity(const Vector3d& vel, const ReferenceFrame& old_frame, const ReferenceFrame& new_frame)
{
	ReferenceFrame rframe = ReferenceFrame(new_frame.Velocity - old_frame.Velocity);

	double gamma = 1.0 / std::sqrt(1.0 - dot(rframe.Velocity, rframe.Velocity));

	return (1.0 / (1.0 - dot(subvec<3>(rframe.Velocity), vel)))
		* (vel / gamma - subvec<3>(rframe.Velocity) + gamma / (gamma + 1)
			* dot(vel, subvec<3>(rframe.Velocity)) * subvec<3>(rframe.Velocity));
}
Vector4d TransformVelocity(const Vector4d& vel, const ReferenceFrame& old_frame,const ReferenceFrame& new_frame)
{
	ReferenceFrame rframe = ReferenceFrame(new_frame.Velocity - old_frame.Velocity);

	double gamma = 1.0 / std::sqrt(1.0 - dot(rframe.Velocity, rframe.Velocity));

	return (1.0 / (1.0 - dot(rframe.Velocity, vel)))
		* (vel / gamma - rframe.Velocity + gamma / (gamma + 1)
			* dot(vel, rframe.Velocity) * rframe.Velocity);
}
