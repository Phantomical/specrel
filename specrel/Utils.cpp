#include "Utils.h"
#include "ObjectBase.h"

constexpr double MinDist = 0.001;

inline double sqr(double v)
{
	return v * v;
}

Ray ReflectRay(const Ray& ray, const Intersection& intersection)
{
	//Formulas grabbed from here: http://arxiv.org/pdf/1207.0998.pdf
	//The formulas used are Equations 9 and 10

	Ray ray_in_frame = TransformRay(ray, intersection.RefFrame);

	double cosalpha = cosangle(subvec<3>(ray_in_frame.Direction), intersection.Normal);
	double velocity = magnitude(intersection.RefFrame.Velocity);

	//TODO: Apply wavelength correction
	//Change when wavelength correction is implemented
#if 0
	//Multiply the spectum by this to realize the relativistic shift
	double factor = (1.0 - 2.0 * velocity * cosalpha + velocity * velocity)
		/ (1.0 - velocity * velocity);

	//Apply factor to spectrum here (somehow)
#endif

	double beta = std::acos((-2.0 * velocity + (1.0 + velocity * velocity) * cosalpha)
		/ (1.0 - 2.0 * velocity * cosalpha + velocity * velocity));

	Vector3d newdir = rotate(intersection.Normal, normalize(
		cross(subvec<3>(ray_in_frame.Direction), intersection.Normal)), -beta);

	return Ray(intersection.Position, Vector4d(newdir, ray_in_frame.Direction.t),
		intersection.RefFrame);
}
Ray RefractRay(const Ray& ray, const Intersection& intersection)
{
	//TODO: Complete this
	//See here: http://www.mathpages.com/rr/s2-08/2-08.htm

	throw 0;
}
