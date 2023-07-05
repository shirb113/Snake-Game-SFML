#pragma once

#include "State.hpp"

#include<stack>
#include<memory>

namespace Engine {

	class StateManager
	{
	private:
		using StateUniquePtr = std::unique_ptr<State>;

	public:
		explicit StateManager();
		~StateManager() = default;

		void Add(StateUniquePtr state_to_add, const bool replace = false);
		void PopCurrentStatus();
		void ProcessStateChange();
		StateUniquePtr& GetCurrentState();

	private:
		std::stack<StateUniquePtr> _state_stack;
		StateUniquePtr _new_state;
		bool _add;
		bool _replace;
		bool _remove;
	};
}
