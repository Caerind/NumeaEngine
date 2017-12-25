#ifndef NU_IMGUIWRAPPER_HPP
#define NU_IMGUIWRAPPER_HPP

#include "../System/Prerequisites.hpp"

#if !defined(NU_ENABLE_IMGUI)
	#if (defined(NU_BUILD_DEBUG))
		#define NU_ENABLE_IMGUI 1
	#else
		#define NU_ENABLE_IMGUI 0
	#endif
#endif

#include "../ExtLibs/imgui/imgui.h"

namespace nu
{

// Encapsulate a block of ImGui code
// Used to execute the encapsulated code only if ImGui is enabled
#define ImGuiWrapper_Begin()
#define ImGuiWrapper_End()

class Window;

namespace ImGuiWrapper
{

bool init(Window& window);
void newFrame();
void preRender();
void render();
void shutdown();

} // namespace ImGuiWrapper

} // namespace nu

// Macros Implementations

#undef ImGuiWrapper_Begin
#undef ImGuiWrapper_End

#if NU_ENABLE_IMGUI == 1

#define ImGuiWrapper_Begin() [&]() { 
#define ImGuiWrapper_End() }();

#else

#define ImGuiWrapper_Begin() [&]() {
#define ImGuiWrapper_End() };

#endif

#endif // NU_IMGUIWRAPPER_HPP