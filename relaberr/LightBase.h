#ifndef SPECREL_LIGHTBASE_H
#define SPECREL_LIGHTBASE_H

#include "ObjectBase.h"
#include "ColourSource.h"

class LightBase
{
protected:
	// A mesh that descripes the shape of the light (This can be NULL)
	// The reference frame and position of this object should be the same as the light
	ObjectBasePtr LightVolume; 

public:
	ObjectBasePtr GetLightVolume() const;

	virtual ReferenceFrame GetRefFrameAtTime(double time) const = 0;
	virtual Position GetPositionAtTime(double time) const = 0;
	virtual ColourSourcePtr GetColourAtTime(double time) const = 0;
	virtual bool IsStatic() const = 0;
	
	virtual ~LightBase() = default;
};

#endif
