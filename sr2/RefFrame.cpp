#include "RefFrame.h"

//This avoids having to explicitly qualify the namespace of Velocity when
//using it within ReferenceFrame
typedef Velocity Vel;

ReferenceFrame::ReferenceFrame(const Vel& v) :
	Velocity(v)
{

}

const ReferenceFrame ReferenceFrame::Default = ReferenceFrame(Vel(0.0, 0.0, 0.0));

Position TransformPosition(const Position& pos, const ReferenceFrame& old, const ReferenceFrame& new_)
{
	ReferenceFrame relative = old.Velocity - new_.Velocity;
	double velocity = magnitude(relative.Velocity);
	Vector3d direction = relative.Velocity * (1.0 / velocity);

	double gamma = 1 / std::sqrt(1.0 - velocity * velocity);

	Vector3d pnew = subvec<3>(pos) + (gamma - 1) * dot<double, 3>(subvec<3>(pos), direction) 
		* direction - gamma * pos.t * velocity * direction;
	double tnew = gamma * (pos.t - velocity * dot(subvec<3>(pos), direction));

	return Position(pnew, tnew);
}
Velocity TransformVelocity(const Velocity& vel, const ReferenceFrame& old, const ReferenceFrame& new_)
{
	ReferenceFrame relative = old.Velocity - new_.Velocity;
	double velocity = magnitude(relative.Velocity);
	Vector3d direction = relative.Velocity * (1.0 / velocity);

	double gamma = 1.0 / std::sqrt(1.0 - velocity * velocity);

	double factor = 1.0 / (1.0 - dot<double, 3>(vel, relative.Velocity));
	Vector3d vector = vel / gamma - (Velocity::BaseType&)relative.Velocity + gamma / (gamma + 1) 
		* dot<double, 3>(vel, relative.Velocity) * relative.Velocity;

	return factor * vector;
}
