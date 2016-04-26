#include "RefFrame.h"

inline double sqr(double v)
{
	return v * v;
}
inline bool approx(double v, double cmp)
{
	return v > cmp - std::numeric_limits<double>::epsilon() 
		&& v < cmp + std::numeric_limits<double>::epsilon();
}

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
	return BoostMatrix(old, new_) * pos;
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

Matrix44d BoostMatrix(const Velocity& beta)
{
	double sqrmag = sqrmagnitude(beta);

	if (approx(sqrmag, 0.0))
		return identity<Matrix44d>();

	double gamma = 1.0 / std::sqrt(1.0 - sqrmag);
	double tmp = (gamma - 1) / sqrmag;

	return Matrix44d(
	{
		gamma, gamma * beta.x, gamma * beta.y, gamma * beta.z,
		gamma * beta.x, 1 + tmp * sqr(beta.x), 1 + tmp * beta.x * beta.y, 1 + tmp * beta.x * beta.z,
		gamma * beta.y, 1 + tmp * beta.x * beta.y, 1 + tmp * sqr(beta.y), 1 + tmp * beta.y * beta.z,
		gamma * beta.z, 1 + tmp * beta.x * beta.z, 1 + tmp * beta.y * beta.z, 1 + tmp * sqr(beta.z)
	});
}
Matrix44d BoostMatrix(const ReferenceFrame& old, const ReferenceFrame& new_)
{
	return BoostMatrix(old.Velocity - new_.Velocity);
}
