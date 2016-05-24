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
	Background(DefaultBackground),
	NumSamples(DefaultNumSamples)
{

}
Frame::Frame(size_t width, size_t height, ScenePtr scene) :
	Image(width, height, 1, 3),
	Scene(scene),
	Background(DefaultBackground),
	NumSamples(DefaultNumSamples)
{

}
Frame::Frame(size_t width, size_t height, ScenePtr scene, const Camera& viewpoint) :
	Image(width, height, 1, 3),
	Scene(scene),
	Viewpoint(viewpoint),
	Background(DefaultBackground),
	NumSamples(DefaultNumSamples)
{

}
Frame::Frame(size_t width, size_t height, ScenePtr scene, const Camera& viewpoint,
	const Colour& background, size_t samples) :
	Image(width, height, 1, 3),
	Scene(scene),
	Viewpoint(viewpoint),
	Background(background),
	NumSamples(samples)
{

}

Colour Frame::TracePoint(const Vector2d& screen_pos) const
{
	//TODO: Add reflection, refraction, and doppler effect calculations
	Ray ray = Viewpoint.CreateRay(screen_pos);

	Intersection isect;
	if (Scene->TryNearestIntersection(ray, isect))
	{
		Colour illuminance = Colour::zero();

		for (auto light : Scene->Lights)
		{
			if (light->Illuminated(isect, MakeRef(Scene)))
			{
				illuminance += light->GetLightIntensity(isect);
			}
		}

		return clamp(isect.GetColour() * illuminance, 0.0f, 1.0f);
	}
	return Background;
}
Colour Frame::GetPixelColour(const vector<size_t, 2>& pixel) const
{
	if (Scene.get() == nullptr)
		throw InvalidStateException("Scene must not be NULL");
	if (NumSamples == 0)
		throw InvalidStateException("NumSamples must not be 0");

	std::random_device rd;
	std::mt19937 engine(pixel.x + pixel.y + rd());
	std::uniform_real_distribution<double> dist(0.0, 1.0);

	Vector2d mul = 1.0 / make_vector<double, double>(Image.width(), Image.height());
	Vector2d pos = 1.0 - static_cast<Vector2d>(pixel * 2) * mul;
	
	std::vector<Colour> samples;
	samples.reserve(NumSamples);

	for (size_t i = 0; i < NumSamples; ++i)
	{
		Vector2d pt = pos - make_vector(dist(engine), dist(engine)) * mul;
		samples.push_back(TracePoint(pt));
	}

	// Average all the samples
	return std::accumulate(samples.begin(), samples.end(), Colour::zero()) / (float)NumSamples;
}

//#define MULTITHREADED
#if !defined _DEBUG
#	define MULTITHREADED
#endif

void Frame::SetFrameSize(size_t width, size_t height)
{
	Image = cil::CImg<typename Colour::value_type>(width, height, 1, 3);
}

void Frame::TracePixel(const vector<size_t, 2>& pixel)
{
	Colour result = GetPixelColour(pixel);

	Image.atXYZC(pixel.x, pixel.y, 0, 0) = result.r; // Red
	Image.atXYZC(pixel.x, pixel.y, 0, 1) = result.g; // Green
	Image.atXYZC(pixel.x, pixel.y, 0, 2) = result.b; // Blue
}
void Frame::TraceFrame()
{
#ifdef MULTITHREADED
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
#ifdef MULTITHREADED
	);
#endif

	cimg_for(Image, ptr, float) 
	{ 
		auto tmp = *ptr * 255.0; 
		*ptr = tmp;
	}
}

void Frame::Save(const char* filename, int suffix, int ndigits) const
{
	Image.save(filename, suffix, ndigits);
}
void Frame::Save() const
{
	Save(FileName.c_str());
}
