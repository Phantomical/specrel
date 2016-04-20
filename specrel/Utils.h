#ifndef SPECREL_UTILS_H
#define SPECREL_UTILS_H

/*
	File for storing various utility functions that I don't know where to put.
*/

#include "Ray.h"
#include "Intersection.h"

Ray ReflectRay(const Ray&, const Intersection&);
Ray RefractRay(const Ray&, const Intersection&);

#endif
