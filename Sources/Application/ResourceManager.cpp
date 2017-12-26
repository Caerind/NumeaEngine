#include "ResourceManager.hpp"

namespace nu
{

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	clear();
}

bool ResourceManager::has(const std::string& str) const
{
	return has(StringId::hash(str));
}

bool ResourceManager::has(U32 id) const
{
	return mResources.find(id) != mResources.end();
}

void ResourceManager::release(const std::string& str)
{
	release(StringId::hash(str));
}

void ResourceManager::release(U32 id)
{
	auto itr = mResources.find(id);
	if (itr == mResources.end())
	{
		LogWarning(LogChannel::Application, 2, "Resource not found : %d", id);
	}
	else
	{
		delete itr->second;
		mResources.erase(itr);
	}
}

void ResourceManager::clear()
{
	for (auto itr = mResources.begin(); itr != mResources.end(); ++itr)
	{
		delete itr->second;
	}
	mResources.clear();
}

} // namespace nu
