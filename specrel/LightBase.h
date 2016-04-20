#ifndef SPECREL_LIGHTBASE_H
#define SPECREL_LIGHTBASE_H

#include "Ray.h"
#include "ObjectBase.h"

class LightBase
{
protected:
	Transform LightTransform;  // The location of the light
	ObjectBasePtr LightVolume; // An object that will be used for reflection (This can be NULL)

public:
	ReferenceFrame GetRefFrame() const;
	Transform GetTransform() const;
	ObjectBasePtr GetLightVolume() const;

	virtual ColourSourcePtr GetColourSource() const = 0;

	virtual ~LightBase() = default;
};

#endif
