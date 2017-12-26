#include "Resource.hpp"

namespace nu
{

BaseResource::BaseResource()
	: mLoaded(false)
	, mId(InvalidU32)
{
}

bool BaseResource::isLoaded() const
{
	return mLoaded;
}

bool BaseResource::isManaged() const
{
	return mId != InvalidU32;
}

U32 BaseResource::getId() const
{
	return mId;
}

} // namespace nu
