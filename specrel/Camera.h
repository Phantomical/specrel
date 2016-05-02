#pragma once

#include "ReferenceFrame.h"
#include "Ray.h"

constexpr inline double Deg2Rad(double deg)
{
	return 0.017453292519943295769 * deg;
}


struct Camera
{
	ReferenceFrame RefFrame;
	Vector4d Position;
	Vector3d Forward;
	Vector3d Up;
	Vector3d Right;
	double FovY;
	double FovX;

	Ray CreateRay(const Vector2d& screen_pos) const;

	Camera() = default;
	Camera(const Vector4d& pos, const ReferenceFrame& ref_frame = ReferenceFrame::Default);
	Camera(double fovx, double fovy);
	Camera(const Vector3d& forward, const Vector3d& up, const Vector3d& right);
	Camera(const Vector4d& pos, const ReferenceFrame& ref_frame,
		const Vector3d& forward, const Vector3d& up, const Vector3d& right,
		double fovy, double fovx);

	static const double DefaultFovX;
	static const double DefaultFovY;
	static const Vector3d DefaultForward;
	static const Vector3d DefaultUp;
	static const Vector3d DefaultRight;
};
