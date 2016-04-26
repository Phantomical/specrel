#include "StaticSphere.h"

Position StaticSphere::GetPosition(double time) const
{
	return Position(Pos, time);
}
ReferenceFrame StaticSphere::GetReferenceFrame(double time) const
{
	return ReferenceFrame::Default;
}
IntersectionList StaticSphere::Intersect(const Ray& ray) const
{
	const double r2 = Radius * Radius;
	const double a = sqrmagnitude(ray.Direction);
	const double b = (ray.Direction * (subvec<3>(ray.Origin) + Pos)).sum();
	const double c = (sqrmagnitude(subvec<3>(ray.Origin))
		+ 2 * dot(subvec<3>(ray.Origin), Pos)
		+ sqrmagnitude(Pos) - r2);

	const double det = b * b - 4 * a * c;

	if (det < 0)
		//No intersections
		return IntersectionList();

	double rtdet = std::sqrt(det);
	double inv2a = 0.5 / a;

	double s1 = (-b + rtdet) * inv2a;
	double s2 = (-b - rtdet) * inv2a;

	Intersection isect1, isect2;
	Vector3d collision;

	collision = ray.Direction * s1 + subvec<3>(ray.Origin);
	isect1.Object = this;
	isect1.Position = Position(collision, ray.Origin.t + s1);
	isect1.Normal = normalize(collision - subvec<3>(ray.Origin));
	isect1.RefFrame = ReferenceFrame::Default;
	isect1.Source = Source;
	isect1.SurfaceVel = Vector3d::zero();

	collision = ray.Direction * s2 + subvec<3>(ray.Origin);
	isect2.Object = this;
	isect2.Position = Position(collision, ray.Origin.t + s2);
	isect2.Normal = normalize(collision - subvec<3>(ray.Origin));
	isect2.RefFrame = ReferenceFrame::Default;
	isect2.Source = Source;
	isect2.SurfaceVel = Vector3d::zero();

	return IntersectionList({ isect1, isect2 });
}

StaticSphere::StaticSphere(const Vector3d& pos, double radius, ColourSourcePtr source) :
	Pos(pos),
	Radius(radius),
	Source(source)
{

}
