#pragma once

#include <stack>
#include <memory>
#include <string>

#include <State.hpp>

namespace Engine
{
	typedef std::unique_ptr<State> StateRef;
	class StateMan
	{
	private:
		std::stack<StateRef> m_stateStack;
		StateRef m_newState;

		bool m_isAdding;
		bool m_isReplacing;
		bool m_isRemoving;

	public:
		StateMan() {}
		~StateMan() {}

		void AddState(StateRef newState, bool isRepalcing = true);
		void RemoveState();
		void ProcessStateChanges();
		StateRef& GetCurrentState();
	};
}
