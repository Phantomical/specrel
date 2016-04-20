#ifndef SPECREL_CAMERA_H
#define SPECREL_CAMERA_H

#include "Transform.h"

struct Camera
{
	Transform Transform;
	Vector3d Forward;
	Vector3d Up;
	Vector3d Right;
	double FovY;
	double FovX;
};

#endif
