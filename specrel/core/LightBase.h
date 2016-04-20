#ifndef SPECREL_LIGHTBASE_H
#define SPECREL_LIGHTBASE_H

#include "ray.h"
#include "object_base.h"

class LightBase
{
protected:
	Transform LightTransform;  // The location of the light
	ObjectBasePtr LightVolume; // An object that will be used for reflection (This can be NULL)

public:
	ReferenceFrame GetRefFrame() const;
	Transform GetTransform() const;
	ObjectBasePtr GetLightVolume() const;

	

	virtual ~LightBase() = default;
};

typedef std::shared_ptr<LightBase> LightBasePtr;

#endif
