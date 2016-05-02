#include "DirectionalLight.h"
#include "Scene.h"

DirectionalLight::DirectionalLight(const Vector3d& dir, const Colour& intensity) :
	Direction(dir),
	Intensity(intensity)
{

}

bool DirectionalLight::Illuminated(const Intersection& isect, SceneRef scene) const
{
	Vector4d npos = LorentzTransform(isect.Position, isect.RefFrame, ReferenceFrame::Default);

	Ray ray = Ray(npos, -Direction, ReferenceFrame::Default, 0.001);

	return !scene->AnyIntersections(ray);
}
Colour DirectionalLight::GetLightIntensity(const Intersection& isect) const
{
	Vector3d ndir = TransformDir(isect.Normal, isect.RefFrame, ReferenceFrame::Default);
	float mul = (float)std::max(cosangle(-Direction, ndir), 0.0);

	return Intensity * mul;
}
