#ifndef NU_RESOURCEPTR_HPP
#define NU_RESOURCEPTR_HPP

#include "Resource.hpp"
#include "ResourceManager.hpp"

namespace nu
{

template <class T>
class ResourcePtr
{
	public:
		NU_STATIC_BASE_OF(BaseResource, T);
		NU_STATIC_BASE_OF(Resource<T>, T);

	public:
		ResourcePtr(T* p = nullptr, ResourceManager* mgr = nullptr);

		ResourcePtr(const ResourcePtr& ptr) = default;
		ResourcePtr& operator=(const ResourcePtr& ptr) = default;
	
		bool operator==(EmptyClass* ptr); // Use only with nullptr
		bool operator!=(EmptyClass* ptr); // Use only with nullptr
		operator bool() const;

		bool isValid() const;

		void invalidate();

		U32 getId() const;

		T& operator*();
		T* operator->();
		T* get();

	private:
		U32 mId;
		T* mPtr;
		ResourceManager* mManager;
};

template<class T>
inline ResourcePtr<T>::ResourcePtr(T* p, ResourceManager* mgr)
	: mId(InvalidU32)
	, mPtr(p)
	, mManager(mgr)
{
	if (p != nullptr)
	{
		mId = p->getId();
	}
}

template<class T>
inline bool ResourcePtr<T>::operator==(EmptyClass* ptr)
{
	return !isValid();
}

template<class T>
inline bool ResourcePtr<T>::operator!=(EmptyClass* ptr)
{
	return isValid();
}

template<class T>
inline ResourcePtr<T>::operator bool() const
{
	return isValid();
}

template<class T>
inline bool ResourcePtr<T>::isValid() const
{
	return mPtr != nullptr && mManager != nullptr && mManager->has(mId);
}

template<class T>
inline void ResourcePtr<T>::invalidate()
{
	mPtr = nullptr;
	mId = InvalidU32;
}

template<class T>
inline U32 ResourcePtr<T>::getId() const
{
	return mId;
}

template<class T>
inline T& ResourcePtr<T>::operator*()
{
	return *mPtr;
}

template<class T>
inline T* ResourcePtr<T>::operator->()
{
	return mPtr;
}

template<class T>
inline T* ResourcePtr<T>::get()
{
	return mPtr;
}

} // namespace nu

#endif // NU_RESOURCEPTR_HPP