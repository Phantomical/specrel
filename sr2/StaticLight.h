#ifndef SPECREL_STATICLIGHT_H
#define SPECREL_STATICLIGHT_H

#include "LightBase.h"

//Base class for all lights that don't move
class StaticLight : public LightBase
{
public:
	virtual Position GetPositionAtTime(double time) const override final;
	virtual Spectrum GetSpectrumAtTime(double time) const override final;
	//Always returns the default reference frame because
	//a static light, by definition, has no velocity
	virtual ReferenceFrame GetRefFrameAtTime(double time) const override final;
	virtual bool IsStatic() const override final;
		
protected:
	virtual Spectrum GetSpectrum() const = 0;

	StaticLight() = default;
	StaticLight(const Vector3d& pos);

	Vector3d Position; // The position of this light, there is no time coordinate because it is adde when GetPositionAtTime is called
};

#endif
