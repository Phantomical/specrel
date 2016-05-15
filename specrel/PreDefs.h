#pragma once

#include "ptr_ref.h"
#include "vector.h"
#include "Defs.h"
#include <memory>


class LightBase;
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
typedef std::shared_ptr<LightBase> LightPtr;
typedef ptr_ref<const LightBase> LightRef;
typedef std::shared_ptr<Frame> FramePtr;
typedef std::shared_ptr<Scene> ScenePtr;
typedef ptr_ref<const Scene> SceneRef;

template<typename vTy, typename... vArgs>
inline std::shared_ptr<vTy> MakePtr(vArgs&&... args)
{
	return std::make_shared<vTy>(args...);
}
template<typename vTy>
inline ptr_ref<const vTy> MakeRef(const std::shared_ptr<vTy>& ptr)
{
	return MakeRef<const vTy>(ptr.get());
}
template<typename vTy>
inline ptr_ref<vTy> MakeRef(vTy* ptr)
{
	return ptr_ref<vTy>(ptr);
}
