#include "Frame.h"
#include <cassert>
#include <random>
#include <ppl.h>

typedef vector<size_t, 2> vec2s;
using std::exception;

#pragma warning(disable:4267)

InvalidStateException::InvalidStateException(const char* msg) :
	exception(msg)
{

}

const Colour Frame::DefaultBackground = Colour(0.0f, 0.0f, 0.0f);

Frame::Frame(size_t width, size_t height) :
	Image(width, height, 1, 3),
	Background(DefaultBackground)
{

}
Frame::Frame(size_t width, size_t height, ScenePtr scene) :
	Image(width, height, 1, 3),
	Scene(scene),
	Background(DefaultBackground)
{

}
Frame::Frame(size_t width, size_t height, ScenePtr scene, const Camera& viewpoint) :
	Image(width, height, 1, 3),
	Scene(scene),
	Viewpoint(viewpoint),
	Background(DefaultBackground)
{

}
Frame::Frame(size_t width, size_t height, ScenePtr scene, const Camera& viewpoint, const Colour& background) :
	Image(width, height, 1, 3),
	Scene(scene),
	Viewpoint(viewpoint),
	Background(background)
{

}

Colour Frame::TracePoint(const Vector2d& screen_pos) const
{
	try
	{
		//TODO: Add reflection, refraction, and doppler effect calculations
		Ray ray = Viewpoint.CreateRay(screen_pos);

		Intersection isect = Scene->NearestIntersection(ray);

		return isect.GetColour();
	}
	catch (NoIntersectionException e)
	{
		return Background;
	}
}
Colour Frame::GetPixelColour(const vec2s& pixel) const
{
	if (Scene.get() == nullptr)
		throw InvalidStateException("Scene must not be NULL");
	if (NumSamples == 0)
		throw InvalidStateException("NumSamples must not be 0");

	std::random_device rd;
	std::mt19937 engine(pixel.x + pixel.y + rd());
	std::uniform_real_distribution<double> dist(-1.0, 1.0);

	Vector2d mul = 1.0 / make_vector<double, double>(Image.width(), Image.height());
	Vector2d pos = static_cast<Vector2d>(pixel) * 2.0 * mul - make_vector(1.0, 1.0);
	

	std::vector<Colour> samples;
	samples.reserve(NumSamples);

	for (size_t i = 0; i < NumSamples; ++i)
	{
		Vector2d pt = pos + make_vector(dist(engine), dist(engine)) * mul;
		samples.push_back(TracePoint(pt));
	}

	// Average all the samples
	return std::accumulate(samples.begin(), samples.end(), Colour::zero()) / (float)NumSamples;
}

void Frame::TracePixel(const vec2s& pixel)
{
	Colour result = GetPixelColour(pixel);

	Image.atXYZC(pixel.x, pixel.y, 0, 0) = result.r; // Red
	Image.atXYZC(pixel.x, pixel.y, 0, 1) = result.g; // Green
	Image.atXYZC(pixel.x, pixel.y, 0, 2) = result.b; // Blue
}
void Frame::TraceFrame()
{
#ifndef _DEBUG
	concurrency::parallel_for(0, Image.height(), [&](size_t y)
#else
	for (size_t y = 0; y < Image.height(); ++y)
#endif
	{
		for (size_t x = 0; x < Image.width(); ++x)
		{
			TracePixel(make_vector<size_t>(x, y));
		}
	}
#ifndef _DEBUG
	);
#endif
}
