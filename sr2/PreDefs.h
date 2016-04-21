#ifndef SPECREL_PREDEFS_
#define SPECREL_PREDEFS_H

#include <memory>

struct RefFrame;
struct Intersection;
struct Velocity;
struct Spectrum;

class ObjectBase;
class LightBase;
class SpectrumSource;

typedef std::shared_ptr<SpectrumSource> SpectrumSourcePtr;
typedef std::shared_ptr<ObjectBase> ObjectBasePtr;
typedef std::shared_ptr<LightBase> LightBasePtr;

#endif
