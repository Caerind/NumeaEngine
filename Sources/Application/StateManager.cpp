#include "StateManager.hpp"
#include "Application.hpp"

namespace nu
{

State::State()
	: mManager(nullptr)
{
}

State::~State()
{
}

void State::onActivate()
{
}

void State::onDeactivate()
{
}

bool State::handleEvent()
{
	return false;
}

bool State::update(Time dt)
{
	return false;
}

void State::render()
{
}

void State::popState()
{
	mManager->popState();
}

void State::clearStates()
{
	mManager->clearStates();
}

Application& State::getApplication()
{
	return mManager->getApplication();
}

StateManager::StateManager(Application& application)
	: mApplication(application)
{
}

StateManager::~StateManager()
{
	for (auto itr = mStates.begin(); itr != mStates.end(); ++itr)
	{
		(*itr)->onDeactivate();
	}
	mStates.clear();
}

void StateManager::handleEvent()
{
	for (auto itr = mStates.rbegin(); itr != mStates.rend(); ++itr)
	{
		if (!(*itr)->handleEvent())
		{
			break;
		}
	}
	applyPendingChanges();
}

void StateManager::update(Time dt)
{
	for (auto itr = mStates.rbegin(); itr != mStates.rend(); ++itr)
	{
		if (!(*itr)->update(dt))
		{
			break;
		}
	}
	applyPendingChanges();
}

void StateManager::render()
{
	for (auto itr = mStates.begin(); itr != mStates.end(); ++itr)
	{
		(*itr)->render();
	}
}

void StateManager::popState()
{
	mChanges.emplace_back(Action::Pop, nullptr);
}

void StateManager::clearStates()
{
	mChanges.emplace_back(Action::Clear, nullptr);
}

U32 StateManager::getStateCount() const
{
	return mStates.size();
}

Application& StateManager::getApplication()
{
	return mApplication;
}

void StateManager::applyPendingChanges()
{
	for (const PendingChange& change : mChanges)
	{
		switch (change.action)
		{
			case Action::Push:
				if (mStates.size() > 0)
				{
					mStates.back()->onDeactivate();
				}
				mStates.push_back(change.state);
				mStates.back()->mManager = this;
				mStates.back()->onActivate();
				break;

			case Action::Pop:
				if (mStates.size() > 0)
				{
					mStates.back()->onDeactivate();
					mStates.pop_back();
				}
				if (mStates.size() > 0)
				{
					mStates.back()->onActivate();
				}
				break;

			case Action::Clear:
				if (mStates.size() > 0)
				{
					mStates.back()->onDeactivate();
				}
				mStates.clear();
				break;
		}
	}
	mChanges.clear();
}

StateManager::PendingChange::PendingChange(Action action, State::Ptr state)
	: action(action)
	, state(state)
{
}

} // namespace nu