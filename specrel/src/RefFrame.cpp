#include "RefFrame.h"

const ReferenceFrame ReferenceFrame::Default = ReferenceFrame(Vector3d(0.0, 0.0, 0.0));

Vector4d TransformPosition(const Vector4d& pos, const ReferenceFrame& old_frame, const ReferenceFrame& new_frame)
{
	ReferenceFrame relative_frame = ReferenceFrame(new_frame.Velocity - old_frame.Velocity);
	double velocity = relative_frame.Velocity.magnitude();
	Vector3d direction = relative_frame.Velocity * (1.0 / velocity);

	double gamma = 1.0 / std::sqrt(1.0 - velocity * velocity);

	// Parallel part of the vector
	Vector3d prl = dot(subvec<3>(pos), direction) * direction;
	// Perpendicular part of the vector
	Vector3d prp = subvec<3>(pos) - prl;

	// Lorentz shifted components
	// New t component
	double tnew = gamma * (pos.t - (dot(prl, relative_frame.Velocity)));
	// New parallel position component (The perpendicular part isn't changed)
	Vector3d pnew = gamma * (prl - relative_frame.Velocity * pos.t);

	return Vector4d(pnew + prp, tnew);
}
Vector3d TransformVelocity(const Vector3d& vel, const ReferenceFrame& old_frame, const ReferenceFrame& new_frame)
{
	ReferenceFrame rframe = ReferenceFrame(new_frame.Velocity - old_frame.Velocity);

	double gamma = 1.0 / std::sqrt(1.0 - dot(rframe.Velocity, rframe.Velocity));

	return (1.0 / (1.0 - dot(rframe.Velocity, vel)))
		* (vel / gamma - rframe.Velocity + gamma / (gamma + 1)
			* dot(vel, rframe.Velocity) * rframe.Velocity);
}
