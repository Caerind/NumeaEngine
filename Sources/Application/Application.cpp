#include "Application.hpp"

namespace nu
{

Application::Application()
	: mStates(*this)
	, mWindow(VideoMode(800, 600), "NumeaEngine")
	, mRenderer(nullptr)
	, mFps(0)
	, mRunning(true)
{
	LogManager::initialize();

	mRenderer = new Renderer();

	#if NU_ENABLE_IMGUI == 1
	ImGuiWrapper::init(mWindow);
	#endif
}

Application::~Application()
{
	#if NU_ENABLE_IMGUI == 1
	ImGuiWrapper::shutdown();
	#endif

	delete mRenderer;

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

Renderer& Application::getRenderer()
{
	return *mRenderer;
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
	Time fpsAccumulator = Time::Zero;
	U32 fpsTemp = 0;
	Clock clock;

	// Running loop
	while (mRunning)
	{
		// Time
		Time dt = clock.restart();

		events();
		preUpdate();
		update(dt);
		postUpdate();
		render();

		// FPS
		fpsTemp++;
		fpsAccumulator += dt;
		if (fpsAccumulator > Time::Second)
		{
			fpsAccumulator -= Time::Second;
			mFps = fpsTemp;
			fpsTemp = 0;
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
	ImGuiWrapper::endFrame();
	#endif
}

void Application::render()
{
	mRenderer->begin();

	mStates.render();

	#if NU_ENABLE_IMGUI == 1
	ImGuiWrapper::render();
	#endif

	mRenderer->end();
	//mWindow.display();
}

} // namespace nu
