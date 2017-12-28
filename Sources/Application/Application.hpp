#ifndef NU_APPLICATION_HPP
#define NU_APPLICATION_HPP

#include "../System/Time.hpp"

#include "Window.hpp"
#include "ImGuiWrapper.hpp"
#include "StateManager.hpp"

#include "../Graphics/Renderer.hpp"

// TODO : This class is broken yet

namespace nu
{

class Application
{
	public:
		Application();
		~Application();

		Window& getWindow();
		Renderer& getRenderer();

		template <typename State, typename ... Args>
		void start(Args&& ... args);

		void stop();

		template <typename T, typename ... Args>
		void pushState(Args&& ... args);
		void popState();
		void clearStates();

		const U32& getFPS() const;

	private:
		void run();
		void events();
		void preUpdate();
		void update(Time dt);
		void postUpdate();
		void render();

	private:
		StateManager mStates;
		Window mWindow;
		Renderer* mRenderer;

		U32 mFps;
		bool mRunning;
};

template <typename State, typename ... Args>
void Application::start(Args&& ... args)
{
	pushState<State>(std::forward<Args>(args)...);

	mStates.applyPendingChanges();

	mRunning = true;

	run();
}

template <typename T, typename ... Args>
void Application::pushState(Args&& ... args)
{
	mStates.pushState<T>(std::forward<Args>(args)...);
}

} // namespace nu

#endif // NU_APPLICATION_HPP
