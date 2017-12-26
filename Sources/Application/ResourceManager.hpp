#ifndef NU_RESOURCEMANAGER_HPP
#define NU_RESOURCEMANAGER_HPP

#include <map>

#include "Resource.hpp"
#include "Loader.hpp"
#include "ResourcePtr.hpp"

#include "../System/String.hpp"

// TODO : Children
// TODO : Known Strategy
// TODO : Memory Allocation

namespace nu
{

class ResourceManager
{
	public:
		ResourceManager();
		~ResourceManager();

		template <class T> ResourcePtr<T> get(const std::string& str);
		template <class T> ResourcePtr<T> get(U32 id);

		template <class T> ResourcePtr<T> get(const std::string& str, const Loader<T>& loader);
		template <class T> ResourcePtr<T> get(U32 id, const Loader<T>& loader);

		bool has(const std::string& str) const;
		bool has(U32 id) const;

		void release(const std::string& str);
		void release(U32 id);

		void clear();

	private:
		template <class T> ResourcePtr<T> load(U32 id, const Loader<T>& loader);

	private:
		std::map<U32, BaseResource*> mResources;
};

template<class T>
inline ResourcePtr<T> ResourceManager::get(const std::string& str)
{
	U32 id = StringId::hash(str);
	auto itr = mResources.find(id);
	if (itr == mResources.end())
	{
		LogWarning(LogChannel::Application, 2, "Resource not found : %d, %s", id, str.c_str());
		return ResourcePtr<T>();
	}
	return ResourcePtr<T>(static_cast<T*>(itr->second), this);
}

template<class T>
inline ResourcePtr<T> ResourceManager::get(U32 id)
{
	auto itr = mResources.find(id);
	if (itr == mResources.end())
	{
		LogWarning(LogChannel::Application, 2, "Resource not found : %d", id);
		return ResourcePtr<T>();
	}
	return ResourcePtr<T>(static_cast<T*>(itr->second), this);
}

template<class T>
inline ResourcePtr<T> ResourceManager::get(const std::string& str, const Loader<T>& loader)
{
	U32 id = StringId::hash(str);
	auto itr = mResources.find(id);
	if (itr != mResources.end())
	{
		LogWarning(LogChannel::Application, 2, "Resource already loaded : %d, %s", id, str.c_str());
		return ResourcePtr<T>(static_cast<T*>(itr->second), this);
	}
	return load(id, loader);
}

template<class T>
inline ResourcePtr<T> ResourceManager::get(U32 id, const Loader<T>& loader)
{
	auto itr = mResources.find(id);
	if (itr != mResources.end())
	{
		LogWarning(LogChannel::Application, 2, "Resource already loaded : %d", id);
		return ResourcePtr<T>(static_cast<T*>(itr->second), this);
	}
	return load(id, loader);
}

template<class T>
inline ResourcePtr<T> ResourceManager::load(U32 id, const Loader<T>& loader)
{
	T* resource = new T();

	resource->mLoaded = loader.load(*resource);
	resource->mId = id;

	mResources.insert(std::make_pair(id, resource));

	return ResourcePtr<T>(resource, this);
}

} // namespace nu

#endif // NU_RESOURCEMANAGER_HPP
