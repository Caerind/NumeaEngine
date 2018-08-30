#ifndef NU_INPUTIMPL_HPP
#define NU_INPUTIMPL_HPP

#include "../../Math/Vector2.hpp"
#include "../../System/String.hpp"
#include "../Keyboard.hpp"
#include "../Mouse.hpp"

namespace nu
{

class InputImpl
{
	public:
		// Keyboard
		static std::string getKeyName(Keyboard::Key key);
		static bool isKeyPressed(Keyboard::Key key);

		// Mouse
		static Vector2i getPosition();
		static Vector2i getPosition(const Window& relativeTo);
		static bool isButtonPressed(Mouse::Button button);
		static void setPosition(const Vector2i& position);
		static void setPosition(const Vector2i& position, const Window& relativeTo);
		static void setPosition(I32 x, I32 y);
		static void setPosition(I32 x, I32 y, const Window& relativeTo);
};

} // namespace nu

#endif // NU_INPUTIMPL_HPP