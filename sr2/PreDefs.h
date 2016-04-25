#ifndef SPECREL_PREDEFS_H
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

namespace detail
{
	template<typename vTy>
	struct mk_shared
	{
		typedef std::shared_ptr<vTy> ptr_type;

		template<typename... vArgs>
		static std::shared_ptr<vTy> make(const vArgs&... args)
		{
			return std::make_shared<vTy>(args...);
		}
	};
	template<typename vTy>
	struct mk_shared<std::shared_ptr<vTy>> : mk_shared<vTy> { };
}

template<typename vTy, typename... vArgs>
inline typename detail::mk_shared<vTy>::ptr_type MakePtr(const vArgs&... args)
{
	return detail::mk_shared<vTy>::make(args...);
}

#endif
