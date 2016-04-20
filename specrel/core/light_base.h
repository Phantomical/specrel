#ifndef SPECREL_LIGHTBASE_H
#define SPECREL_LIGHTBASE_H

#include "ray.h"

class LightBase
{
protected:
	Transform LightTransform;       // The location of the light

public:
	ReferenceFrame GetRefFrame() const;
	Transform GetTransform() const;

	//Indicates whether a ray would be illuminated by this light, and,
	//if it does, returns the colour that the ray would be in light_colour
	virtual bool Illuminates(const Ray&, Colour& light_colour) const = 0;

	virtual ~LightBase() = default;
};

#endif
