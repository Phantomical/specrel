#pragma once

#include "Scene.h"
#include "Camera.h"
#ifdef _MSC_VER
#pragma warning( push, 0 )
#include <CodeAnalysis\Warnings.h>
#pragma warning( disable : ALL_CODE_ANALYSIS_WARNINGS )
#endif
#include <CImg.h>
#ifdef _MSC_VER
#pragma warning( pop )
#endif

class InvalidStateException : std::exception
{
public:
	InvalidStateException() = default;
	InvalidStateException(const char* msg);
};

struct Frame
{
private:
	cil::CImg<typename Colour::value_type> Image;

public:
	ScenePtr Scene;
	Camera Viewpoint;
	Colour Background;
	size_t NumSamples;

	Frame(size_t width, size_t height);
	Frame(size_t width, size_t height, ScenePtr scene);
	Frame(size_t width, size_t height, ScenePtr scene, const Camera& viewpoint);
	Frame(size_t width, size_t height, ScenePtr scene, const Camera& viewpoint, const Colour& background, size_t num_samples = DefaultNumSamples);

	Colour TracePoint(const Vector2d& screen_pos) const;
	Colour GetPixelColour(const vector<size_t, 2>& position) const;
	void TracePixel(const vector<size_t, 2>& position);
	void TraceFrame();


	//Saves the file and optionally adds a suffix at the end of the filename
	void Save(const char* filename, int suffix = -1, int ndigits = 6) const;

	static const Colour DefaultBackground;
	static constexpr size_t DefaultNumSamples = 16;
};
