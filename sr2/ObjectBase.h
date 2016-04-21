#ifndef SPECREL_OBJECTBASE_H
#define SPECREL_OBJECTBASE_H

#include "RefFrame.h"

class ObjectBase
{
public:
	virtual Position GetPosition(double time) const = 0;
	virtual ReferenceFrame GetReferenceFrame(double time) const = 0;

	virtual ~ObjectBase() = default;
};

#endif
