#include "Camera.h"

constexpr inline double deg2rad(double deg)
{
	return 0.017453292519943295769 * deg;
}

const double Camera::DefaultFovX = deg2rad(80);
const double Camera::DefaultFovY = deg2rad(60);
const Vector3d Camera::DefaultForward = Vector3d(0, 0, 1);
const Vector3d Camera::DefaultUp = Vector3d(0, 1, 0);
const Vector3d Camera::DefaultRight = Vector3d(1, 0, 0);

Ray Camera::CreateRay(const Vector2d& screen_pos) const
{
	const double halfsizex = std::tan(FovX * 0.5);
	const double halfsizey = std::tan(FovY * 0.5);

	Vector3d dir = normalize(Forward + Right * halfsizex * screen_pos[0] + Up * halfsizey * screen_pos[1]);
	return Ray(Position, dir, RefFrame);
}

Camera::Camera(const Vector4d& pos, const ReferenceFrame& ref_frame) :
	RefFrame(ref_frame),
	Position(pos),
	Forward(DefaultForward),
	Up(DefaultUp),
	Right(DefaultRight),
	FovY(DefaultFovY),
	FovX(DefaultFovX)
{

}
Camera::Camera(double fovx, double fovy) :
	RefFrame(ReferenceFrame::Default),
	Position(Vector4d::zero()),
	Forward(DefaultForward),
	Up(DefaultUp),
	Right(DefaultRight),
	FovY(fovy),
	FovX(fovx)
{

}
Camera::Camera(const Vector3d& forward, const Vector3d& up, const Vector3d& right) :
	RefFrame(ReferenceFrame::Default),
	Position(Vector4d::zero()),
	Forward(forward),
	Up(up),
	Right(right),
	FovY(DefaultFovY),
	FovX(DefaultFovX)
{

}
Camera::Camera(const Vector4d& pos, const ReferenceFrame& ref_frame,
		const Vector3d& forward, const Vector3d& up, const Vector3d& right,
		double fovy, double fovx) :
	RefFrame(ref_frame),
	Position(pos),
	Forward(forward),
	Up(up),
	Right(right),
	FovY(fovy),
	FovX(fovx)
{

}
