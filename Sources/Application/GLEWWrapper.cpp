#include "GLEWWrapper.hpp"

namespace nu
{

namespace GLEWWrapper
{

namespace priv
{

bool initialized = false;

} // namespace priv

bool isInitialized()
{
	return priv::initialized;
}

bool init()
{
	if (!priv::initialized)
	{
		glewExperimental = true; // Needed in core profile
		if (glewInit() != GLEW_OK)
		{
			LogError(nu::LogChannel::Application, 10, "Failed to initialize GLEW");
			priv::initialized = false;
		}
		else
		{
			priv::initialized = true;
		}
	}
	return priv::initialized;
}

} // namespace GLEWWrapper

} // namespace nu