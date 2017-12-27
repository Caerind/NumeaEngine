#ifndef NU_RESOURCE_HPP
#define NU_RESOURCE_HPP

#include "../System/Prerequisites.hpp"
#include "Loader.hpp"

namespace nu
{

template <class T>
class ResourcePtr;
class ResourceManager;

class BaseResource
{
	public:
		BaseResource();

		bool isLoaded() const;
		bool isManaged() const;
		U32 getId() const;

	protected:
		bool mLoaded;

	private:
		friend class ResourceManager;
		U32 mId;
};

template <class T>
class Resource : public BaseResource
{
	public:
		typedef ResourcePtr<T> Ptr;
};

} // namespace nu

#endif // NU_RESOURCE_HPP