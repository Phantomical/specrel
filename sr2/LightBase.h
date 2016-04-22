#ifndef SPECREL_LIGHTBASE_H
#define SPECREL_LIGHTBASE_H

#include "ObjectBase.h"
#include "Spectrum.h"

class LightBase
{
protected:
	ObjectBasePtr LightVolume; // A mesh that descripes the shape of the light (This can be NULL)

public:
	ObjectBasePtr GetLightVolume() const;

	virtual Position GetPositionAtTime(double time) const = 0;
	virtual Spectrum GetSpectrumAtTime(double time) const = 0;
	virtual bool IsStatic() const = 0;
	
	virtual ~LightBase() = default;
};

#endif
