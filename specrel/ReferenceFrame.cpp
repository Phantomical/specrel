#include "ReferenceFrame.h"
#include <cmath>

const ReferenceFrame ReferenceFrame::Default = ReferenceFrame(Vector3d(0.0, 0.0, 0.0));

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
	ReferenceFrame change = old - new_;

	double gamma = change.Gamma();
	double vel = magnitude(change.Velocity);

	// If there is no change between frames
	// don't do anything
	if (vel == 0.0)
		return pos;

	Vector3d dir = change.Velocity / vel;

	return Vector4d(subvec<3>(pos) + (gamma - 1) * dot(subvec<3>(pos), dir) * dir 
		- gamma * pos.t * vel * dir, gamma * (pos.t - vel * dot(dir, subvec<3>(pos))));
}
Vector3d LorentzTransform(const Vector3d& vel, const ReferenceFrame& old, const ReferenceFrame& new_)
{
	ReferenceFrame change = old - new_;

	// If there is no change between frames
	// don't do anything
	if (sqrmagnitude(change.Velocity) == 0.0)
		return vel;

	return (ReferenceFrame(vel) + change).Velocity;
}

namespace
{
	constexpr double PI = 3.1415926535897932385;
	inline bool approx(double v, double cmp)
	{
		return v > cmp - std::numeric_limits<double>::epsilon()
			&& v < cmp + std::numeric_limits<double>::epsilon();
	}
}

Vector3d TransformDir(const Vector3d& dir, const ReferenceFrame& old, const ReferenceFrame& new_)
{
	ReferenceFrame change = old - new_;

	Vector3d vdir = normalize(change.Velocity);
	double vel = magnitude(change.Velocity);
	double cosalpha = cosangle(vdir, dir);

	if (cosalpha == 1.0 || vel == 0.0)
		return dir;

	double beta = std::acos((cosalpha - vel) / (1 - vel * cosalpha));

	return rotate(vdir, normalize(cross(dir, vdir)), beta);
}
