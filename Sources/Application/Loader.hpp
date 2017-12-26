#ifndef NU_LOADER_HPP
#define NU_LOADER_HPP

#include <functional>
#include <type_traits>

#include "Resource.hpp"

namespace nu
{

template <class T>
class Loader
{
	public:
		NU_STATIC_BASE_OF(BaseResource, T);

		typedef std::function<bool(T&)> LoaderFunc;

	public:
		Loader(LoaderFunc loader);

		bool load(T& resource) const;

	private:
		LoaderFunc mLoader;
};

template<class T>
inline Loader<T>::Loader(LoaderFunc loader)
	: mLoader(std::move(loader))
{
}

template<class T>
inline bool Loader<T>::load(T& resource) const
{
	return mLoader(resource);
}

} // namespace nu

#endif // NU_LOADER_HPP
