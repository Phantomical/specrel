#pragma once

#include "PreDefs.h"
#include "vector.h"

class ColourSource
{
public:
	virtual Colour GetRGB() const = 0;

	virtual ~ColourSource() = default;
};
