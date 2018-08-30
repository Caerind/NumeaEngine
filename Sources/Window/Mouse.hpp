#ifndef NU_MOUSE_HPP
#define NU_MOUSE_HPP

#include "../Math/Vector2.hpp"

namespace nu
{

class Window;

class Mouse
{
	public:
		Mouse() = delete;
		~Mouse() = delete;

		enum Button
		{
			Left,
			Middle,
			Right,
			XButton1,
			XButton2,

			Count
		};

		static Vector2i getPosition();
		static Vector2i getPosition(const Window& relativeTo);
		static bool isButtonPressed(Button button);
		static void setPosition(const Vector2i& position);
		static void setPosition(const Vector2i& position, const Window& relativeTo);
		static void setPosition(I32 x, I32 y);
		static void setPosition(I32 x, I32 y, const Window& relativeTo);
};

} // namespace nu

#endif // NU_MOUSE_HPP