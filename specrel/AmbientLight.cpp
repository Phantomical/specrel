#include "AmbientLight.h"

bool AmbientLight::Illuminated(const Intersection&, SceneRef) const
{
	// Every point is illuminated by an ambient light
	return true;
}
Colour AmbientLight::GetLightIntensity(const Intersection&) const
{
	return Intensity;
}

AmbientLight::AmbientLight(const Colour& intensity) :
	Intensity(intensity)
{

}
