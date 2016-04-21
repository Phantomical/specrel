#ifndef SPECREL_LIGHTBASE_H
#define SPECREL_LIGHTBASE_H

#include "ObjectBase.h"

class LightBase
{
protected:
	ObjectBasePtr LightVolume;

public:
	ObjectBasePtr GetLightVolume() const;

	virtual Position GetPositionAtTime(double time) const = 0;
	virtual bool IsStatic() const = 0;
	
	virtual ~LightBase() = default;
};

#endif
