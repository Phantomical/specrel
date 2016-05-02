#pragma once

#include "Intersection.h"
#include "ReferenceFrame.h"

class LightBase
{
protected:
	ReferenceFrame RefFrame;

	LightBase() = default;
	LightBase(const ReferenceFrame& ref_frame);

public:
	// Indicates that the intersection is illuminated by the light
	virtual bool Illuminated(const Intersection& isect, SceneRef scene) const = 0;
	// Returns the intensity of the light at the intersection, this
	// method doesn't have to calculate whether the ray intersects
	// with the scene. It should assume that it doesn't.
	virtual Colour GetLightIntensity(const Intersection& isect) const = 0;

	// Returns the reference frame of this light.
	ReferenceFrame GetRefFrame() const;

	virtual ~LightBase() = default;
};
