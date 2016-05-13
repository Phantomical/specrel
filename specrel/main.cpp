#include "Frame.h"
#include "Sphere.h"
#include "RgbColourSource.h"
#include "DirectionalLight.h"
#include "AmbientLight.h"

int main()
{
	ScenePtr scene = MakePtr<Scene>();

#if 1
	ColourSourcePtr source1 = MakePtr<RgbColourSource>(Colour(1.0f, 0.0f, 0.0f));
	ColourSourcePtr source2 = MakePtr<RgbColourSource>(Colour(0.0f, 1.0f, 0.0f));
	ColourSourcePtr source3 = MakePtr<RgbColourSource>(Colour(0.0f, 0.0f, 1.0f));
	ColourSourcePtr source4 = MakePtr<RgbColourSource>(Colour(1.0f, 1.0f, 1.0f));

	scene->AddObject(MakePtr<Sphere>(Vector4d(1.5, -0.5, 0.0, 0.0), 2.5, source1));
	scene->AddObject(MakePtr<Sphere>(Vector4d(-1.5, -0.5, 0.0, 0.0), 2.5, source2));
	scene->AddObject(MakePtr<Sphere>(Vector4d(0.0, 1.2, 0.0, 0.0), 2.5, source3));
	scene->AddObject(MakePtr<Sphere>(Vector4d(0.0, -25003.0, 0.0), 25000.0, source4));
#else
	ColourSourcePtr source = MakePtr<RgbColourSource>(Colour(1.0f, 1.0f, 1.0f));
	ObjectPtr sphere = MakePtr<Sphere>(Vector4d(0.0, 0.0, 0.0, 0.0), 2.5, source);
	ObjectPtr sphere4 = MakePtr<Sphere>(Vector4d(0.0, -25003.0, 0.0), 25000.0, source);

	scene->AddObject(sphere4);
	scene->AddObject(sphere);
#endif

	scene->AddLight(MakePtr<DirectionalLight>(Vector3d(0.0, -1.0, 0.0), Colour(1.0f, 1.0f, 1.0f)));
	scene->AddLight(MakePtr<AmbientLight>(Colour(0.1f, 0.1f, 0.1f)));

	Camera viewpoint = Camera(Vector4d(0.0, 0.0, -15.0, 0.0), ReferenceFrame(Vector3d(0.0, 0.0, 0.0)));
	viewpoint.FovX = Deg2Rad(80);
	viewpoint.FovY = Deg2Rad(60);

	viewpoint.Forward = Vector3d(0.0, 0.0, 1.0);
	viewpoint.Up = Vector3d(0.0, 1.0, 0.0);
	viewpoint.Right = Vector3d(1.0, 0.0, 0.0);

	Frame frame = Frame(1000, 750, scene, viewpoint, Colour(0.0f, 0.0f, 0.0f), 64);

	frame.TraceFrame();

	frame.Save("output.bmp");

	return 0;
}
