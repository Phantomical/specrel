#pragma once

#include "Scene.h"
#include "Camera.h"
#ifdef _MSC_VER
#include <codeanalysis\warnings.h>
#pragma warning( push )
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#pragma warning ( disable : 4319 )
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
	Frame(size_t width, size_t height, ScenePtr scene, const Camera& viewpoint, const Colour& background);

	Colour TracePoint(const Vector2d& screen_pos) const;
	Colour GetPixelColour(const vector<size_t, 2>& position) const;
	void TracePixel(const vector<size_t, 2>& position);
	void TraceFrame();
	

	//Saves the file and optionally adds a suffix at the end of the filename
	void Save(const char* filename, int suffix = -1, int ndigits = 6);

	static const Colour DefaultBackground;
};
