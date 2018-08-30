#include "WindowImpl.hpp"

#include "../../System/String.hpp"

namespace nu
{

static U32 gWindowCount = 0; 
static const wchar_t* gClassName = L"Window";

WindowImpl::WindowImpl(WindowHandle handle)
	: mHandle((HWND)handle)
	, mCallback(0)
	, mLastCursor(LoadCursor(NULL, IDC_ARROW))
	, mResizing(false)
	, mLastSize(0, 0)
	, mEvents()
{
	if (mHandle != nullptr)
	{
		SetWindowLongPtrW(mHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
		mCallback = SetWindowLongPtrW(mHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&WindowImpl::globalOnEvent));
	}
}

WindowImpl::WindowImpl(const VideoMode& mode, const std::string& title)
	: mHandle(nullptr)
	, mCallback(0)
	, mLastCursor(LoadCursor(NULL, IDC_ARROW))
	, mEvents()
{
	// Register class
	if (gWindowCount == 0)
	{
		registerWindowClass();
	}

	// Compute position and size
	HDC screenDC = GetDC(NULL);
	I32 left = (GetDeviceCaps(screenDC, HORZRES) - static_cast<I32>(mode.width)) / 2;
	I32 top = (GetDeviceCaps(screenDC, VERTRES) - static_cast<I32>(mode.height)) / 2;
	I32 width = mode.width;
	I32 height = mode.height;
	ReleaseDC(NULL, screenDC);

	// Style
	DWORD win32Style = WS_VISIBLE | WS_SYSMENU;

	// In windowed mode, adjust width and height so that window will have the requested client area
	if (true)
	{
		RECT rectangle = { 0, 0, width, height };
		AdjustWindowRect(&rectangle, win32Style, false);
		width = rectangle.right - rectangle.left;
		height = rectangle.bottom - rectangle.top;
	}

	mHandle = CreateWindowW(gClassName, toWideString(title).c_str(), win32Style, left, top, width, height, NULL, NULL, GetModuleHandle(NULL), this);

	// By default, the OS limits the size of the window the the desktop size, we have to resize it after creation to apply the real size
	setSize(Vector2u(mode.width, mode.height));

	gWindowCount++;
}

WindowImpl::~WindowImpl()
{
	if (mCallback != 0)
	{
		if (mHandle != nullptr)
		{
			DestroyWindow(mHandle);
		}
		gWindowCount--;
		if (gWindowCount == 0)
		{
			UnregisterClassW(gClassName, GetModuleHandleW(NULL));
		}
	}
	else
	{
		// Disconnect callback
		SetWindowLongPtrW(mHandle, GWLP_WNDPROC, mCallback);
	}
}

bool WindowImpl::popEvent(Event& event, bool block)
{
	// Get events from OS
	if (mEvents.size() == 0)
	{
		processEvents();
		if (block)
		{
			while (mEvents.empty())
			{
				Sleep(10);
				processEvents();
			}
		}
	}

	// Give one event to user
	if (mEvents.size() >= 1)
	{
		event = mEvents.front();
		mEvents.pop();
		return true;
	}

	return false;
}

void WindowImpl::pushEvent(const Event& event)
{
	mEvents.push(event);
}

void WindowImpl::setPosition(I32 x, I32 y)
{
	setPosition(Vector2i(x, y));
}

void WindowImpl::setPosition(const Vector2i& position)
{
	SetWindowPos(mHandle, NULL, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

Vector2i WindowImpl::getPosition() const
{
	RECT rect;
	GetWindowRect(mHandle, &rect);
	return Vector2i(rect.left, rect.top);
}

void WindowImpl::setSize(U32 width, U32 height)
{
	setSize(Vector2u(width, height));
}

void WindowImpl::setSize(const Vector2u& size)
{
	RECT rectangle = { 0, 0, static_cast<long>(size.x), static_cast<long>(size.y) };
	AdjustWindowRect(&rectangle, GetWindowLong(mHandle, GWL_STYLE), false);
	I32 width = rectangle.right - rectangle.left;
	I32 height = rectangle.bottom - rectangle.top;
	SetWindowPos(mHandle, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
}

Vector2u WindowImpl::getSize() const
{
	RECT rect;
	GetClientRect(mHandle, &rect);
	return Vector2u(rect.right - rect.left, rect.bottom - rect.top);
}

void WindowImpl::requestFocus()
{
	DWORD thisPid = GetWindowThreadProcessId(mHandle, NULL);
	DWORD currentPid = GetWindowThreadProcessId(GetForegroundWindow(), NULL);
	if (thisPid == currentPid) // In the same thread : steal focus
	{
		SetForegroundWindow(mHandle);
	}
	else // Different threads : notifications
	{ 
		FLASHWINFO info;
		info.cbSize = sizeof(info);
		info.hwnd = mHandle;
		info.dwFlags = FLASHW_TRAY;
		info.dwTimeout = 0;
		info.uCount = 3;
		FlashWindowEx(&info);
	}
}

bool WindowImpl::hasFocus() const
{
	return mHandle == GetForegroundWindow();
}

WindowHandle WindowImpl::getSystemHandle() const
{
	return mHandle;
}

void WindowImpl::processEvents()
{
	// We process the window events only if we own it
	if (mCallback == 0)
	{
		MSG message;
		while (PeekMessageW(&message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessageW(&message);
		}
	}
}

void WindowImpl::registerWindowClass()
{
	WNDCLASSW windowClass;
	windowClass.style = 0;
	windowClass.lpfnWndProc = &WindowImpl::globalOnEvent;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandleW(NULL);
	windowClass.hIcon = NULL;
	windowClass.hCursor = 0;
	windowClass.hbrBackground = 0;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = gClassName;
	RegisterClassW(&windowClass);
}

void WindowImpl::setTracking(bool track)
{
	TRACKMOUSEEVENT mouseEvent;
	mouseEvent.cbSize = sizeof(TRACKMOUSEEVENT);
	mouseEvent.dwFlags = track ? TME_LEAVE : TME_CANCEL;
	mouseEvent.hwndTrack = mHandle;
	mouseEvent.dwHoverTime = HOVER_DEFAULT;
	TrackMouseEvent(&mouseEvent);
}

void WindowImpl::cleanup()
{
	setTracking(false);
	ReleaseCapture();
}

Keyboard::Key WindowImpl::translateVirtualKeyCode(WPARAM key, LPARAM flags)
{
	switch (key)
	{
		case VK_CONTROL:	return (HIWORD(flags) & KF_EXTENDED) ? Keyboard::RControl : Keyboard::LControl;
		case VK_MENU:		return (HIWORD(flags) & KF_EXTENDED) ? Keyboard::RAlt : Keyboard::LAlt;
		case VK_SHIFT:
		{
			static UINT scancode = MapVirtualKey(VK_SHIFT, MAPVK_VK_TO_VSC);
			return (((flags >> 16) & 0xFF) == scancode) ? Keyboard::LShift : Keyboard::RShift;
		}
		case 0x30:                 return Keyboard::Num0;
		case 0x31:                 return Keyboard::Num1;
		case 0x32:                 return Keyboard::Num2;
		case 0x33:                 return Keyboard::Num3;
		case 0x34:                 return Keyboard::Num4;
		case 0x35:                 return Keyboard::Num5;
		case 0x36:                 return Keyboard::Num6;
		case 0x37:                 return Keyboard::Num7;
		case 0x38:                 return Keyboard::Num8;
		case 0x39:                 return Keyboard::Num9;
		case 0x41:                 return Keyboard::A;
		case 0x42:                 return Keyboard::B;
		case 0x43:                 return Keyboard::C;
		case 0x44:                 return Keyboard::D;
		case 0x45:                 return Keyboard::E;
		case 0x46:                 return Keyboard::F;
		case 0x47:                 return Keyboard::G;
		case 0x48:                 return Keyboard::H;
		case 0x49:                 return Keyboard::I;
		case 0x4A:                 return Keyboard::J;
		case 0x4B:                 return Keyboard::K;
		case 0x4C:                 return Keyboard::L;
		case 0x4D:                 return Keyboard::M;
		case 0x4E:                 return Keyboard::N;
		case 0x4F:                 return Keyboard::O;
		case 0x50:                 return Keyboard::P;
		case 0x51:                 return Keyboard::Q;
		case 0x52:                 return Keyboard::R;
		case 0x53:                 return Keyboard::S;
		case 0x54:                 return Keyboard::T;
		case 0x55:                 return Keyboard::U;
		case 0x56:                 return Keyboard::V;
		case 0x57:                 return Keyboard::W;
		case 0x58:                 return Keyboard::X;
		case 0x59:                 return Keyboard::Y;
		case 0x5A:                 return Keyboard::Z;
		case VK_ADD:               return Keyboard::Add;
		case VK_BACK:              return Keyboard::Backspace;
		case VK_BROWSER_BACK:      return Keyboard::Browser_Back;
		case VK_BROWSER_FAVORITES: return Keyboard::Browser_Favorites;
		case VK_BROWSER_FORWARD:   return Keyboard::Browser_Forward;
		case VK_BROWSER_HOME:      return Keyboard::Browser_Home;
		case VK_BROWSER_REFRESH:   return Keyboard::Browser_Refresh;
		case VK_BROWSER_SEARCH:    return Keyboard::Browser_Search;
		case VK_BROWSER_STOP:      return Keyboard::Browser_Stop;
		case VK_CAPITAL:           return Keyboard::CapsLock;
		case VK_CLEAR:             return Keyboard::Clear;
		case VK_DECIMAL:           return Keyboard::Decimal;
		case VK_DELETE:            return Keyboard::Delete;
		case VK_DIVIDE:            return Keyboard::Divide;
		case VK_DOWN:              return Keyboard::Down;
		case VK_END:               return Keyboard::End;
		case VK_ESCAPE:            return Keyboard::Escape;
		case VK_F1:                return Keyboard::F1;
		case VK_F2:                return Keyboard::F2;
		case VK_F3:                return Keyboard::F3;
		case VK_F4:                return Keyboard::F4;
		case VK_F5:                return Keyboard::F5;
		case VK_F6:                return Keyboard::F6;
		case VK_F7:                return Keyboard::F7;
		case VK_F8:                return Keyboard::F8;
		case VK_F9:                return Keyboard::F9;
		case VK_F10:               return Keyboard::F10;
		case VK_F11:               return Keyboard::F11;
		case VK_F12:               return Keyboard::F12;
		case VK_F13:               return Keyboard::F13;
		case VK_F14:               return Keyboard::F14;
		case VK_F15:               return Keyboard::F15;
		case VK_HOME:              return Keyboard::Home;
		case VK_INSERT:            return Keyboard::Insert;
		case VK_LEFT:              return Keyboard::Left;
		case VK_LWIN:              return Keyboard::LSystem;
		case VK_MEDIA_NEXT_TRACK:  return Keyboard::Media_Next;
		case VK_MEDIA_PLAY_PAUSE:  return Keyboard::Media_Play;
		case VK_MEDIA_PREV_TRACK:  return Keyboard::Media_Previous;
		case VK_MEDIA_STOP:        return Keyboard::Media_Stop;
		case VK_MULTIPLY:          return Keyboard::Multiply;
		case VK_NEXT:              return Keyboard::PageDown;
		case VK_NUMPAD0:           return Keyboard::Numpad0;
		case VK_NUMPAD1:           return Keyboard::Numpad1;
		case VK_NUMPAD2:           return Keyboard::Numpad2;
		case VK_NUMPAD3:           return Keyboard::Numpad3;
		case VK_NUMPAD4:           return Keyboard::Numpad4;
		case VK_NUMPAD5:           return Keyboard::Numpad5;
		case VK_NUMPAD6:           return Keyboard::Numpad6;
		case VK_NUMPAD7:           return Keyboard::Numpad7;
		case VK_NUMPAD8:           return Keyboard::Numpad8;
		case VK_NUMPAD9:           return Keyboard::Numpad9;
		case VK_NUMLOCK:           return Keyboard::NumLock;
		case VK_OEM_1:             return Keyboard::Semicolon;
		case VK_OEM_2:             return Keyboard::Slash;
		case VK_OEM_3:             return Keyboard::Tilde;
		case VK_OEM_4:             return Keyboard::LBracket;
		case VK_OEM_5:             return Keyboard::Backslash;
		case VK_OEM_6:             return Keyboard::RBracket;
		case VK_OEM_7:             return Keyboard::Quote;
		case VK_OEM_COMMA:         return Keyboard::Comma;
		case VK_OEM_MINUS:         return Keyboard::Dash;
		case VK_OEM_PERIOD:        return Keyboard::Period;
		case VK_OEM_PLUS:          return Keyboard::Equal;
		case VK_RIGHT:             return Keyboard::Right;
		case VK_PRIOR:             return Keyboard::PageUp;
		case VK_PAUSE:             return Keyboard::Pause;
		case VK_PRINT:             return Keyboard::Print;
		case VK_SCROLL:            return Keyboard::ScrollLock;
		case VK_SNAPSHOT:          return Keyboard::PrintScreen;
		case VK_SUBTRACT:          return Keyboard::Subtract;
		case VK_RETURN:            return Keyboard::Return;
		case VK_RWIN:              return Keyboard::RSystem;
		case VK_SPACE:             return Keyboard::Space;
		case VK_TAB:               return Keyboard::Tab;
		case VK_UP:                return Keyboard::Up;
		case VK_VOLUME_DOWN:       return Keyboard::Volume_Down;
		case VK_VOLUME_MUTE:       return Keyboard::Volume_Mute;
		case VK_VOLUME_UP:         return Keyboard::Volume_Up;
	}
	return Keyboard::Unknown;
}

void WindowImpl::processEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
	// Don't process anything if window isn't created
	if (mHandle == nullptr)
	{
		return;
	}

	switch (message)
	{
		// Destroy event
		case WM_DESTROY: cleanup(); break;

		// Set cursor event
		case WM_SETCURSOR:
		{
			// The mouse has moved, if the cursor is in our window we must refresh the cursor
			if (LOWORD(lParam) == HTCLIENT)
			{
				SetCursor(mLastCursor);
			}
			break;
		}

		// Close event
		case WM_CLOSE:
		{
			Event event;
			event.type = Event::Closed;
			pushEvent(event);
			break;
		}

		// Resize event
		case WM_SIZE:
		{
			// Consider only events triggered by a maximize or a un-maximize
			if (wParam != SIZE_MINIMIZED && !mResizing && mLastSize != getSize())
			{
				// Update the last handled size
				mLastSize = getSize();

				// Push a resize event
				Event event;
				event.type = Event::Resized;
				event.size.width = mLastSize.x;
				event.size.height = mLastSize.y;
				pushEvent(event);
			}
			break;
		}

		// Start resizing
		case WM_ENTERSIZEMOVE:
		{
			mResizing = true;
			break;
		}

		// Stop resizing
		case WM_EXITSIZEMOVE:
		{
			mResizing = false;

			// Ignore cases where the window has only been moved
			if (mLastSize != getSize())
			{
				// Update the last handled size
				mLastSize = getSize();

				// Push a resize event
				Event event;
				event.type = Event::Resized;
				event.size.width = mLastSize.x;
				event.size.height = mLastSize.y;
				pushEvent(event);
			}
			break;
		}

		// The system request the min/max window size and position
		case WM_GETMINMAXINFO:
		{
			// We override the returned information to remove the default limit (the OS doesn't allow windows bigger than the desktop by default)
			MINMAXINFO* info = reinterpret_cast<MINMAXINFO*>(lParam);
			info->ptMaxTrackSize.x = 50000;
			info->ptMaxTrackSize.y = 50000;
			break;
		}

		// Gain focus event
		case WM_SETFOCUS:
		{
			Event event;
			event.type = Event::GainedFocus;
			pushEvent(event);
			break;
		}

		// Lost focus event
		case WM_KILLFOCUS:
		{
			Event event;
			event.type = Event::LostFocus;
			pushEvent(event);
			break;
		}

		// Text event
		case WM_CHAR:
		{
			if (mKeyRepeatEnabled || ((lParam & (1 << 30)) == 0))
			{
				// Get the code of the typed character
				U32 character = static_cast<U32>(wParam);

				// Check if it is the first part of a surrogate pair, or a regular character
				if ((character >= 0xD800) && (character <= 0xDBFF))
				{
					// First part of a surrogate pair: store it and wait for the second one
					mSurrogate = static_cast<U16>(character);
				}
				else
				{
					// Check if it is the second part of a surrogate pair, or a regular character
					if ((character >= 0xDC00) && (character <= 0xDFFF))
					{
						// Convert the UTF-16 surrogate pair to a single UTF-32 value
						U16 utf16[] = { mSurrogate, static_cast<U16>(character) };
						//sf::Utf16::toUtf32(utf16, utf16 + 2, &character);
						mSurrogate = 0;
					}

					// Send a TextEntered event
					Event event;
					event.type = Event::TextEntered;
					event.text.unicode = character;
					pushEvent(event);
				}
			}
			break;
		}

		// Keydown event
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
			if (mKeyRepeatEnabled || ((HIWORD(lParam) & KF_REPEAT) == 0))
			{
				Event event;
				event.type = Event::KeyPressed;
				event.key.alt = HIWORD(GetKeyState(VK_MENU)) != 0;
				event.key.control = HIWORD(GetKeyState(VK_CONTROL)) != 0;
				event.key.shift = HIWORD(GetKeyState(VK_SHIFT)) != 0;
				event.key.system = HIWORD(GetKeyState(VK_LWIN)) || HIWORD(GetKeyState(VK_RWIN));
				event.key.code = translateVirtualKeyCode(wParam, lParam);
				pushEvent(event);
			}
			break;
		}

		// Keyup event
		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			Event event;
			event.type = Event::KeyReleased;
			event.key.alt = HIWORD(GetKeyState(VK_MENU)) != 0;
			event.key.control = HIWORD(GetKeyState(VK_CONTROL)) != 0;
			event.key.shift = HIWORD(GetKeyState(VK_SHIFT)) != 0;
			event.key.system = HIWORD(GetKeyState(VK_LWIN)) || HIWORD(GetKeyState(VK_RWIN));
			event.key.code = translateVirtualKeyCode(wParam, lParam);
			pushEvent(event);
			break;
		}

		// Vertical mouse wheel event
		case WM_MOUSEWHEEL:
		{
			// Mouse position is in screen coordinates, convert it to window coordinates
			POINT position;
			position.x = static_cast<I16>(LOWORD(lParam));
			position.y = static_cast<I16>(HIWORD(lParam));
			ScreenToClient(mHandle, &position);

			I16 delta = static_cast<I16>(HIWORD(wParam));

			Event event;
			event.type = Event::MouseWheel;
			event.mouseWheel.delta = static_cast<float>(delta) / 120.f;
			event.mouseWheel.x = position.x;
			event.mouseWheel.y = position.y;
			pushEvent(event);
			break;
		}

		// Mouse left button down event
		case WM_LBUTTONDOWN:
		{
			Event event;
			event.type = Event::MouseButtonPressed;
			event.mouseButton.button = Mouse::Left;
			event.mouseButton.x = static_cast<I16>(LOWORD(lParam));
			event.mouseButton.y = static_cast<I16>(HIWORD(lParam));
			pushEvent(event);
			break;
		}

		// Mouse left button up event
		case WM_LBUTTONUP:
		{
			Event event;
			event.type = Event::MouseButtonReleased;
			event.mouseButton.button = Mouse::Left;
			event.mouseButton.x = static_cast<I16>(LOWORD(lParam));
			event.mouseButton.y = static_cast<I16>(HIWORD(lParam));
			pushEvent(event);
			break;
		}

		// Mouse right button down event
		case WM_RBUTTONDOWN:
		{
			Event event;
			event.type = Event::MouseButtonPressed;
			event.mouseButton.button = Mouse::Right;
			event.mouseButton.x = static_cast<I16>(LOWORD(lParam));
			event.mouseButton.y = static_cast<I16>(HIWORD(lParam));
			pushEvent(event);
			break;
		}

		// Mouse right button up event
		case WM_RBUTTONUP:
		{
			Event event;
			event.type = Event::MouseButtonReleased;
			event.mouseButton.button = Mouse::Right;
			event.mouseButton.x = static_cast<I16>(LOWORD(lParam));
			event.mouseButton.y = static_cast<I16>(HIWORD(lParam));
			pushEvent(event);
			break;
		}

		// Mouse wheel button down event
		case WM_MBUTTONDOWN:
		{
			Event event;
			event.type = Event::MouseButtonPressed;
			event.mouseButton.button = Mouse::Middle;
			event.mouseButton.x = static_cast<I16>(LOWORD(lParam));
			event.mouseButton.y = static_cast<I16>(HIWORD(lParam));
			pushEvent(event);
			break;
		}

		// Mouse wheel button up event
		case WM_MBUTTONUP:
		{
			Event event;
			event.type = Event::MouseButtonReleased;
			event.mouseButton.button = Mouse::Middle;
			event.mouseButton.x = static_cast<I16>(LOWORD(lParam));
			event.mouseButton.y = static_cast<I16>(HIWORD(lParam));
			pushEvent(event);
			break;
		}

		// Mouse X button down event
		case WM_XBUTTONDOWN:
		{
			Event event;
			event.type = Event::MouseButtonPressed;
			event.mouseButton.button = HIWORD(wParam) == XBUTTON1 ? Mouse::XButton1 : Mouse::XButton2;
			event.mouseButton.x = static_cast<I16>(LOWORD(lParam));
			event.mouseButton.y = static_cast<I16>(HIWORD(lParam));
			pushEvent(event);
			break;
		}

		// Mouse X button up event
		case WM_XBUTTONUP:
		{
			Event event;
			event.type = Event::MouseButtonReleased;
			event.mouseButton.button = HIWORD(wParam) == XBUTTON1 ? Mouse::XButton1 : Mouse::XButton2;
			event.mouseButton.x = static_cast<I16>(LOWORD(lParam));
			event.mouseButton.y = static_cast<I16>(HIWORD(lParam));
			pushEvent(event);
			break;
		}

		// Mouse leave event
		case WM_MOUSELEAVE:
		{
			// Avoid this firing a second time in case the cursor is dragged outside
			if (mMouseInside)
			{
				mMouseInside = false;

				// Generate a MouseLeft event
				Event event;
				event.type = Event::MouseLeft;
				pushEvent(event);
			}
			break;
		}

		// Mouse move event
		case WM_MOUSEMOVE:
		{
			// Extract the mouse local coordinates
			int x = static_cast<I16>(LOWORD(lParam));
			int y = static_cast<I16>(HIWORD(lParam));

			// Get the client area of the window
			RECT area;
			GetClientRect(mHandle, &area);

			// Capture the mouse in case the user wants to drag it outside
			if ((wParam & (MK_LBUTTON | MK_MBUTTON | MK_RBUTTON | MK_XBUTTON1 | MK_XBUTTON2)) == 0)
			{
				// Only release the capture if we really have it
				if (GetCapture() == mHandle)
				{
					ReleaseCapture();
				}
			}
			else if (GetCapture() != mHandle)
			{
				// Set the capture to continue receiving mouse events
				SetCapture(mHandle);
			}

			// If the cursor is outside the client area...
			if ((x < area.left) || (x > area.right) || (y < area.top) || (y > area.bottom))
			{
				// and it used to be inside, the mouse left it.
				if (mMouseInside)
				{
					mMouseInside = false;

					// No longer care for the mouse leaving the window
					setTracking(false);

					// Generate a MouseLeft event
					Event event;
					event.type = Event::MouseLeft;
					pushEvent(event);
				}
			}
			else
			{
				// and vice-versa
				if (!mMouseInside)
				{
					mMouseInside = true;

					// Look for the mouse leaving the window
					setTracking(true);

					// Generate a MouseEntered event
					Event event;
					event.type = Event::MouseEntered;
					pushEvent(event);
				}
			}

			// Generate a MouseMove event
			Event event;
			event.type = Event::MouseMoved;
			event.mouseMove.x = x;
			event.mouseMove.y = y;
			pushEvent(event);
			break;
		}

		default: break;
	}
}

LRESULT CALLBACK WindowImpl::globalOnEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Associate handle and Window instance when the creation message is received
	if (message == WM_CREATE)
	{
		// Get WindowImplWin32 instance (it was passed as the last argument of CreateWindow)
		LONG_PTR window = (LONG_PTR)reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams;

		// Set as the "user data" parameter of the window
		SetWindowLongPtrW(handle, GWLP_USERDATA, window);
	}

	// Get the WindowImpl instance corresponding to the window handle
	WindowImpl* window = handle ? reinterpret_cast<WindowImpl*>(GetWindowLongPtr(handle, GWLP_USERDATA)) : NULL;

	// Forward the event to the appropriate function
	if (window)
	{
		window->processEvent(message, wParam, lParam);
		if (window->mCallback)
		{
			return CallWindowProcW(reinterpret_cast<WNDPROC>(window->mCallback), handle, message, wParam, lParam);
		}
	}

	// We don't forward the WM_CLOSE message to prevent the OS from automatically destroying the window
	if (message == WM_CLOSE)
	{
		return 0;
	}

	// Don't forward the menu system command, so that pressing ALT or F10 doesn't steal the focus
	if ((message == WM_SYSCOMMAND) && (wParam == SC_KEYMENU))
	{
		return 0;
	}

	return DefWindowProcW(handle, message, wParam, lParam);
}

} // namespace nu
