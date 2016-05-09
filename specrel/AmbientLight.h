#pragma once

#include "LightBase.h"

// A light that illuminates all parts of the scene
class AmbientLight : public LightBase
{
public:
	Colour Intensity;

	virtual bool Illuminated(const Intersection& isect, SceneRef scene) const final override;
	virtual Colour GetLightIntensity(const Intersection& isect) const final override;

	AmbientLight() = default;
	AmbientLight(const Colour& intensity);
};
