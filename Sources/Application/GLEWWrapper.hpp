#ifndef NU_GLEWWRAPPER_HPP
#define NU_GLEWWRAPPER_HPP

#include "../System/Prerequisites.hpp"

#include <GL/glew.h>

namespace nu
{

namespace GLEWWrapper
{

bool isInitialized();
bool init();

} // namespace GLEWWrapper

} // namespace nu

#endif // NU_GLEWWRAPPER_HPP