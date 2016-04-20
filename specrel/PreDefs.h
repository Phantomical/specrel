#ifndef SPECREL_PREDEFS_H
#define SPECREL_PREDEFS_H

#include <memory>

/* Structs */

struct Intersection;
struct Medium;
struct Camera;
struct ReferenceFrame;
struct Transform;

/* Classes */

class ObjectBase;
class Scene;
class ColourSource;
class LightBase;
class Ray;

/* Typedefs */

typedef std::shared_ptr<ObjectBase> ObjectBasePtr;
typedef std::shared_ptr<ColourSource> ColourSourcePtr;
typedef std::shared_ptr<LightBase> LightBasePtr;

#endif
