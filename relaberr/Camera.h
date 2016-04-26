#ifndef SPECREL_CAMERA_
#define SPECREL_CAMERA_H

#include "RefFrame.h"

struct Camera
{
	ReferenceFrame RefFrame; // Reference frame of the camera
	Position Position;       // The position of the camera
	Vector3d Forward;        // A vector that points forward relative to the viewpoint of the camera
	Vector3d Right;          // A vector that points right relative to the viewpoint of the camera
	Vector3d Up;             // A vector that points up relative to the viewpoint of the camera
	double FovY;             // The vertical field of view of the camera
	double FovX;             // The horizontal field of view of the camera
};

#endif
