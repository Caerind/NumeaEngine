#ifndef NU_EVENT_HPP
#define NU_EVENT_HPP

#include "Keyboard.hpp"
#include "Mouse.hpp"

namespace nu
{

class Event
{
	public:
		struct KeyEvent
		{
			Keyboard::Key code;
			bool alt;
			bool control;
			bool shift;
			bool system;
		};

		struct MouseButtonEvent
		{
			Mouse::Button button;
			I32 x;
			I32 y;
		};

		struct MouseMoveEvent
		{
			I32 deltaX;
			I32 deltaY;
			I32 x;
			I32 y;
		};

		struct MouseWheelEvent
		{
			F32 delta;
			I32 x;
			I32 y;
		};

		struct PositionEvent
		{
			I32 x;
			I32 y;
		};

		struct SizeEvent
		{
			U32 width;
			U32 height;
		};

		struct TextEvent
		{
			char unicode;
		};

		enum EventType
		{
			Closed,
			Resized,
			Moved,
			LostFocus,
			GainedFocus,
			TextEntered,
			KeyPressed,
			KeyReleased,
			MouseWheel,
			MouseButtonPressed,
			MouseButtonReleased,
			MouseMoved,
			MouseEntered,
			MouseLeft,

			Count
		};

		EventType type;

		union
		{
			KeyEvent              key;
			MouseButtonEvent      mouseButton;
			MouseMoveEvent        mouseMove;
			MouseWheelEvent       mouseWheel;
			PositionEvent		  position;
			SizeEvent             size;
			TextEvent             text;
		};
};

} // namespace nu

#endif // NU_EVENT_HPP
