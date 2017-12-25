#include "Application.hpp"

namespace nu
{

Application::Application()
	: mStates(*this)
	, mWindow()
	, mFpsAccumulator(Time::Zero)
	, mFpsTemp(0)
	, mFps(0)
	, mRunning(true)
{
	#if NU_ENABLE_IMGUI == 1
	ImGuiWrapper::init(mWindow);
	#endif
}

Application::~Application()
{
	#if NU_ENABLE_IMGUI == 1
	ImGuiWrapper::shutdown();
	#endif

	if (mWindow.isOpen())
	{
		mWindow.close();
	}

	#ifdef NU_PLATFORM_MOBILE
	std::exit(0);
	#endif
}

Window& Application::getWindow()
{
	return mWindow;
}

void Application::stop()
{
	mRunning = false;
}

void Application::popState()
{
	mStates.popState();
}

void Application::clearStates()
{
	mStates.clearStates();
}

const U32& Application::getFPS() const
{
	return mFps;
}

void Application::run()
{
	const Time TimePerFrame = seconds(1.0f / 60.0f);
	Time accumulator = Time::Zero;
	Clock clock;

	// Running loop
	while (mRunning)
	{
		// Time
		Time dt = clock.restart();
		accumulator += dt;
		mFpsAccumulator += dt;

		// Usefull when using Breakpoints on Debugging
		#ifdef NU_BUILD_DEBUG
		if (accumulator > Time::Second)
		{
			accumulator = TimePerFrame;
		}
		#endif

		// Update
		while (accumulator >= TimePerFrame)
		{
			accumulator -= TimePerFrame;

			events();;
			preUpdate();
			update(TimePerFrame);
			postUpdate();
		}

		// Rendering
		render();

		// FPS
		mFpsTemp++;
		if (mFpsAccumulator > Time::Second)
		{
			mFpsAccumulator -= Time::Second;
			mFps = mFpsTemp;
			mFpsTemp = 0;
		}

		// Stop ?
		if (!mWindow.isOpen() || mStates.getStateCount() == 0)
		{
			stop();
		}
	}
}

void Application::events()
{
	mStates.handleEvent();
}

void Application::preUpdate()
{
}

void Application::update(Time dt)
{
	#if NU_ENABLE_IMGUI == 1
	ImGuiWrapper::newFrame();
	#endif

	mStates.update(dt);
}

void Application::postUpdate()
{
	#if NU_ENABLE_IMGUI == 1
	ImGuiWrapper::preRender();
	#endif
}

void Application::render()
{
	mWindow.clear();

	mStates.render();

	#if NU_ENABLE_IMGUI == 1
	ImGuiWrapper::render();
	#endif

	mWindow.display();
}

} // namespace nu
