#include "ReferenceFrame.h"
#include <cmath>

double ReferenceFrame::Gamma() const
{
	return 1.0 / sqrt(1.0 - sqrmagnitude(Velocity));
}

ReferenceFrame::ReferenceFrame(const Vector3d& vel) :
	Velocity(vel)
{

}

ReferenceFrame operator +(const ReferenceFrame& u, const ReferenceFrame& v)
{
	const double factor = 1.0 / (1.0 + dot(u.Velocity, v.Velocity));
	const double gamma = u.Gamma();
	return ReferenceFrame(factor * (u.Velocity + v.Velocity * (1.0 / gamma) + (gamma / (1.0 + gamma)) * dot(u.Velocity, v.Velocity) * u.Velocity));
}
ReferenceFrame operator -(const ReferenceFrame& u, const ReferenceFrame& v)
{
	return u + -v;
}

ReferenceFrame operator +(const ReferenceFrame& u)
{
	return u;
}
ReferenceFrame operator -(const ReferenceFrame& u)
{
	return ReferenceFrame(-u.Velocity);
}

Vector4d LorentzTransform(const Vector4d& pos, const ReferenceFrame& old, const ReferenceFrame& new_)
{
	ReferenceFrame change = new_ - old;

	double gamma = change.Gamma();
	double vel = magnitude(change.Velocity);
	Vector3d dir = change.Velocity / vel;

	return Vector4d(change.Velocity + (gamma - 1) * dot(subvec<3>(pos), dir) * dir 
		- gamma * pos.t * vel * dir, gamma * (pos.t - vel * dot(dir, subvec<3>(pos))));
}
Vector3d LorentzTransform(const Vector3d& vel, const ReferenceFrame& old, const ReferenceFrame& new_)
{
	ReferenceFrame change = new_ - old;
	return (ReferenceFrame(vel) + change).Velocity;
}