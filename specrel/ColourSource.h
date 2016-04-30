#pragma once

#include "PreDefs.h"

class ColourSource
{
public:
	virtual Colour GetColour(const Intersection&) const = 0;

	virtual ~ColourSource() = default;
};
