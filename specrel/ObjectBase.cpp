#include "ObjectBase.h"

bool ObjectBase::AnyIntersections(const Ray& ray) const
{
	return AllIntersections(ray).empty();
}
