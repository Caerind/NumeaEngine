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
			fprintf(stderr, "GLEWWrapper : Failed to initialize GLEW\n");
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