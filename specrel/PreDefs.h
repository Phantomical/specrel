#pragma once

#include "ptr_ref.h"
#include "vector.h"
#include <memory>

class ObjectBase;

struct ReferenceFrame;
struct Intersection;
struct Ray;
struct Scene;

typedef std::shared_ptr<ObjectBase> ObjectPtr;
typedef ptr_ref<const ObjectBase> ObjectRef;
typedef std::shared_ptr<Scene> ScenePtr;
typedef ptr_ref<const Scene> SceneRef;
