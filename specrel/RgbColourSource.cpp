#include "RgbColourSource.h"

RgbColourSource::RgbColourSource(const Colour& colour) :
	RgbValue(colour)
{

}

Colour RgbColourSource::GetColour() const
{
	return RgbValue;
}
Colour RgbColourSource::GetColour(const Intersection&) const
{
	return GetColour();
}
bool RgbColourSource::GetColour(Colour& out) const
{
	out = GetColour();
	return true;
}
