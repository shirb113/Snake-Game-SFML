#include "StateManager.hpp"

Engine::StateManager::StateManager() :
	_add(false),
	_replace(false),
	_remove(false)
{
}

void Engine::StateManager::Add(StateUniquePtr state_to_add, const bool replace)
{
	_add = true;
	_new_state = std::move(state_to_add);
	_replace = replace;
}

void Engine::StateManager::PopCurrentStatus()
{
	_remove = true;
}

void Engine::StateManager::ProcessStateChange()
{
	if ((_remove) && (!_state_stack.empty()))
	{
		_state_stack.pop();

		if (!_state_stack.empty())
		{
			_state_stack.top()->Start();
		}

		_remove = false;
	}

	if (_add)
	{
		if ((_remove) && (!_state_stack.empty()))
		{
			_state_stack.pop();
			_replace = false;
		}

		if (!_state_stack.empty())
		{
			_state_stack.top()->Pause();
		}

		_state_stack.push(std::move(_new_state));
		_state_stack.top()->Init();
		_state_stack.top()->Start();
		_add = false;
		}
}

Engine::StateManager::StateUniquePtr& Engine::StateManager::GetCurrentState()
{
	return _state_stack.top();
}

