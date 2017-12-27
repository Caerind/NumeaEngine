#ifndef NU_LOADER_HPP
#define NU_LOADER_HPP

#include <functional>

#include "../System/Prerequisites.hpp"

namespace nu
{

class BaseResource;

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

template <class T>
class Saver
{
	public:
		NU_STATIC_BASE_OF(BaseResource, T);

		typedef std::function<bool(T&)> SaverFunc;

	public:
		Saver(SaverFunc saver);

		bool save(T& resource) const;

	private:
		SaverFunc mSaver;
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

template<class T>
inline Saver<T>::Saver(SaverFunc saver)
	: mSaver(std::move(saver))
{
}

template<class T>
inline bool Saver<T>::save(T& resource) const
{
	return mSaver(resource);
}

} // namespace nu

#endif // NU_LOADER_HPP
