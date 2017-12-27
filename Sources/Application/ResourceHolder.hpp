#ifndef NU_RESOURCEHOLDER_HPP
#define NU_RESOURCEHOLDER_HPP

#include "ResourceManager.hpp"

namespace nu
{

class ResourceHolder
{
	public:
		ResourceHolder(ResourceManager& manager);
		~ResourceHolder();

		template <class T> ResourcePtr<T> get(const std::string& str);
		template <class T> ResourcePtr<T> get(U32 id);

		template <class T> ResourcePtr<T> get(const std::string& str, const Loader<T>& loader, ResourceManager::KnownStrategy known = ResourceManager::KnownStrategy::Reuse);
		template <class T> ResourcePtr<T> get(U32 id, const Loader<T>& loader, ResourceManager::KnownStrategy known = ResourceManager::KnownStrategy::Reuse);

		bool has(const std::string& str) const;
		bool has(U32 id) const;

		bool own(const std::string& str) const;
		bool own(U32 id) const;

		void release(const std::string& str, bool onlyOwned = true);
		void release(U32 id, bool onlyOwned = true);

		void clear();

	private:
		ResourceManager& mManager;
		std::vector<U32> mOwned;
};

template<class T>
inline ResourcePtr<T> ResourceHolder::get(const std::string& str)
{
	return mManager.get<T>(str);
}

template<class T>
inline ResourcePtr<T> ResourceHolder::get(U32 id)
{
	return mManager.get<T>(id);
}

template<class T>
inline ResourcePtr<T> ResourceHolder::get(const std::string& str, const Loader<T>& loader, ResourceManager::KnownStrategy known)
{
	ResourcePtr<T> ptr = mManager.get<T>(str, loader, known);
	if (ptr.isValid())
	{
		mOwned.push_back(ptr->getId());
	}
	return ptr;
}

template<class T>
inline ResourcePtr<T> ResourceHolder::get(U32 id, const Loader<T>& loader, ResourceManager::KnownStrategy known)
{
	ResourcePtr<T> ptr = mManager.get<T>(id, loader, known);
	if (ptr.isValid())
	{
		mOwned.push_back(ptr->getId());
	}
	return ptr;
}

} // namespace nu

#endif // NU_RESOURCEHOLDER_HPP
