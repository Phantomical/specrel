#include "core/ray.h"

Ray::Ray(const Vector4d& origin, const Vector4d& dir, const ReferenceFrame& ref_frame, const double weight) :
	Origin(origin),
	Direction(dir),
	RefFrame(ref_frame),
	SumWeight(weight)
{

}
Ray::Ray(const Transform& origin, const Vector4d& dir, const double weight) :
	RefFrame(origin.RefFrame),
	Direction(dir),
	Origin(origin.Position),
	SumWeight(weight)
{

}
