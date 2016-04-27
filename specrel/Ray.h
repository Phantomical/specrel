#pragma once

#include "ReferenceFrame.h"

// Represents a light ray traced backwards
struct Ray
{
	double MinDistance;	     // The minimum distance that must be crossed by the ray before it can intersect with anything
	Vector3d Direction;	     // The direction that the ray is travelling in
	Vector4d Origin;	     // The point that the ray originated from
	ReferenceFrame RefFrame; // The reference frame that the ray coordinates are in

	Vector4d GetFourVelocity() const;

	Ray() = default;
	Ray(const Vector4d& origin, const Vector3d& direction, const ReferenceFrame& ref_frame = ReferenceFrame::Default, double min_dist = 0.001);
};

Ray LorentzTransform(const Ray& ray, const ReferenceFrame& new_);
