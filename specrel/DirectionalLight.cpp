#include "DirectionalLight.h"
#include "Scene.h"

DirectionalLight::DirectionalLight(const Vector3d& dir, const Colour& intensity) :
	Direction(normalize(dir)),
	Intensity(intensity)
{

}

bool DirectionalLight::Illuminated(const Intersection& isect, SceneRef scene) const
{
	Vector4d npos = LorentzTransform(isect.Position, isect.RefFrame, ReferenceFrame::Default);

	Ray ray = Ray(npos, -Direction, ReferenceFrame::Default, 0.01);

	return !scene->AnyIntersections(ray);
}
Colour DirectionalLight::GetLightIntensity(const Intersection& isect) const
{
	Vector3d ndir = TransformDir(isect.Normal, isect.RefFrame, ReferenceFrame::Default);

	return Intensity * (float)std::max(dot(ndir, -Direction), 0.0);
}
