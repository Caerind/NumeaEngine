#include "ResourceHolder.hpp"

namespace nu
{

ResourceHolder::ResourceHolder(ResourceManager& manager)
	: mManager(manager)
	, mOwned()
{
}

ResourceHolder::~ResourceHolder()
{
	clear();
}

bool ResourceHolder::has(const std::string& str) const
{
	return mManager.has(str);
}

bool ResourceHolder::has(U32 id) const
{
	return mManager.has(id);
}

bool ResourceHolder::own(const std::string& str) const
{
	return own(StringId::hash(str));
}

bool ResourceHolder::own(U32 id) const
{
	for (U32 i = 0; i < mOwned.size(); i++)
	{
		if (mOwned[i] == id)
		{
			return true;
		}
	}
	return false;
}

void ResourceHolder::release(const std::string& str, bool onlyOwned)
{
	release(StringId::hash(str), onlyOwned);
}

void ResourceHolder::release(U32 id, bool onlyOwned)
{
	if (onlyOwned)
	{
		U32 size = mOwned.size();
		for (U32 i = 0; i < size; i++)
		{
			if (mOwned[i] == id)
			{
				mManager.release(id);
				mOwned.erase(mOwned.begin() + i);
				i--;
				size--;
			}
		}
	}
	else
	{
		mManager.release(id);
	}
}

void ResourceHolder::clear()
{
	for (U32 i = 0; i < mOwned.size(); i++)
	{
		mManager.release(mOwned[i]);
	}
	mOwned.clear();
}

} // namespace nu
