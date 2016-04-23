#ifndef SPECREL_VELOCITY_
#define SPECREL_VELOCITY_H

#include "vector.h"
#include "PreDefs.h"

struct Velocity : Vector3d
{
	typedef Vector3d BaseType;

	Velocity() = default;
	Velocity(const double* v) :
		BaseType(v)
	{

	}
	Velocity(const BaseType& v) :
		BaseType(v)
	{

	}
	Velocity(double x, double y, double z) :
		Vector3d(x, y, z)
	{

	}

	double Gamma() const
	{
		return 1.0 / std::sqrt(1.0 - dot(*this, *this));
	}
};

inline Velocity operator-(const Velocity& v)
{
	return -v;
}
inline Velocity operator+(const Velocity& v)
{
	return v;
}

inline Velocity operator +(const Velocity& u, const Velocity& v)
{
	double gamma = u.Gamma();
	double factor = 1.0 / (1.0 + dot(u, v));
	return ((Velocity::BaseType&)u + (Velocity::BaseType&)v + gamma / (1 + gamma) * cross(u, cross(u, v))) * factor;
}
inline Velocity operator -(const Velocity& u, const Velocity& v)
{
	return u + -v;
}

inline Velocity& operator+=(Velocity& v, const Velocity& u)
{
	return v = v + u;
}
inline Velocity& operator-=(Velocity& v, const Velocity& u)
{
	return v = v - u;
}

#endif
