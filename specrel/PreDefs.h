#pragma once

#include "ptr_ref.h"
#include "vector.h"
#include <memory>

class ObjectBase;
class ColourSource;

struct Ray;
struct Scene;
struct Frame;
struct Camera;
struct Intersection;
struct ReferenceFrame;

typedef std::shared_ptr<ColourSource> ColourSourcePtr;
typedef std::shared_ptr<ObjectBase> ObjectPtr;
typedef ptr_ref<const ObjectBase> ObjectRef;
typedef std::shared_ptr<Scene> ScenePtr;
typedef ptr_ref<const Scene> SceneRef;
