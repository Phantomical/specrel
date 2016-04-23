#include "Frame.h"



Vector2s Frame::ImageSize() const
{
	return Vector2s(Image.width(), Image.height());
}
void Frame::Save(const std::string& name, int digits, int ndigits) const
{
	Image.save(name.c_str(), digits, ndigits);
}

#pragma warning(disable:4267)
Frame::Frame(const Vector2s& size) :
	Image(size.x, size.y, 1, 3),
	FrameScene(nullptr)
{

}
Frame::Frame(const Vector2s& size, const Camera& viewpoint) :
	Image(size.x, size.y, 1, 3),
	FrameScene(nullptr),
	Viewpoint(viewpoint)
{

}
Frame::Frame(const Vector2s& size, const Camera& viewpoint, ScenePtr scene) :
	Image(size.x, size.y),
	FrameScene(scene),
	Viewpoint(viewpoint)
{

}

Ray Frame::CreateRay(const Vector2d& pixel, bool trace_forward) const
{
	const double halfsizex = std::tan(Viewpoint.FovX * 0.5);
	const double halfsizey = std::tan(Viewpoint.FovY * 0.5);

	Vector3d space_dir = normalize(Viewpoint.Forward + Viewpoint.Right * pixel[0] + Viewpoint.Up * pixel[1]);
	
	return Ray(space_dir, Viewpoint.Position, trace_forward ? 1.0 : -1.0, Viewpoint.RefFrame);
}

void Frame::DrawPixel(const Vector2s& pixel)
{

}
