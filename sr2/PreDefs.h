#ifndef SPECREL_PREDEFS_
#define SPECREL_PREDEFS_H

#include <memory>

struct ReferenceFrame;
struct Intersection;
struct Velocity;
struct Spectrum;
struct LightRayInfo;
struct SpectrumData;

class ObjectBase;
class LightBase;
class SpectrumSource;

typedef std::shared_ptr<SpectrumSource> SpectrumSourcePtr;
typedef std::shared_ptr<ObjectBase> ObjectBasePtr;
typedef std::shared_ptr<LightBase> LightBasePtr;
typedef std::shared_ptr<SpectrumData> SpectrumDataPtr;

#endif
