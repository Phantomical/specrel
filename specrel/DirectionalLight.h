#pragma once

#include "LightBase.h"

// A directional light
class DirectionalLight : public LightBase
{
public:
	Vector3d Direction; // The direction that the light from this light is going in.
	Colour Intensity;   // The intensity of the light (This is constant throughout the scene).

	virtual bool Illuminated(const Intersection& isect, SceneRef scene) const final override;
	virtual Colour GetLightIntensity(const Intersection& isect) const final override;

	DirectionalLight() = default;
	DirectionalLight(const Vector3d& dir, const Colour& intensity);
};
