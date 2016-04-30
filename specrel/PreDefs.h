#pragma once

#include "ptr_ref.h"
#include "vector.h"
#include <memory>

class ObjectBase;

struct ReferenceFrame;
struct Intersection;
struct Ray;

typedef std::shared_ptr<ObjectBase> ObjectPtr;
typedef ptr_ref<const ObjectBase> ObjectRef;
