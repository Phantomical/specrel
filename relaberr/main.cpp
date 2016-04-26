#include "Frame.h"
#include "StaticPointLight.h"
#include "StandardColourSource.h"

int main()
{
	ScenePtr scene = MakePtr<ScenePtr>();
	ColourSourcePtr red = MakePtr<ColourSource>(new StandardColourSource(Colour(1.0f, 0.0f, 0.0f)));

	scene->Lights.push_back(MakePtr<LightBasePtr>(new StaticPointLight(Vector3d(0, 0, 0), red)));
	
}
