#ifndef NU_STATEMANAGER_HPP
#define NU_STATEMANAGER_HPP

#include <memory>

#include "../System/Time.hpp"

namespace nu
{

class Application;
class StateManager;

class State
{
	public:
		State(StateManager& manager);
		virtual ~State();

		using Ptr = std::shared_ptr<State>;

		virtual void onActivate();
		virtual void onDeactivate();

		virtual bool handleEvent();
		virtual bool update(Time dt);
		virtual void render();

		template <typename T, typename ... Args>
		void pushState(Args&& ... args);
		void popState();
		void clearStates();

		Application& getApplication();

	private:
		StateManager& mManager;
};

class StateManager
{
	public:
		StateManager(Application& application);
		~StateManager();

		void handleEvent();
		void update(Time dt);
		void render();

		template <typename T, typename ... Args>
		void pushState(Args&& ... args);
		void popState();
		void clearStates();

		U32 getStateCount() const;

		Application& getApplication();

		void applyPendingChanges();

	private:
		enum Action
		{
			Push,
			Pop,
			Clear
		};

		struct PendingChange
		{
			PendingChange(Action action, State::Ptr state);

			Action action;
			State::Ptr state;
		};

	private:
		Application& mApplication;
		std::vector<State::Ptr> mStates;
		std::vector<PendingChange> mChanges;
};

template <typename T, typename ... Args>
void State::pushState(Args&& ... args)
{
	mManager.pushState<T>(std::forward<Args>(args)...);
}

template <typename T, typename ... Args>
void StateManager::pushState(Args&& ... args)
{
	mChanges.emplace_back(Action::Push, std::make_shared<T>(*this, std::forward<Args>(args)...));
}

} // namespace nu

#endif // NU_STATEMANAGER_HPP
