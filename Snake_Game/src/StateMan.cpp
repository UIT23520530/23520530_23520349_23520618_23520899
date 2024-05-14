#include <StateMan.hpp>

namespace Engine
{
	void StateMan::AddState(StateRef newState, bool isReplacing)
	{
		m_isAdding = true;
		m_isReplacing = isReplacing;

		m_newState = std::move(newState);
	}
	
	void StateMan::RemoveState()
	{
		m_isRemoving = true;
	}

	void StateMan::ProcessStateChanges()
	{
		if (m_isRemoving && !m_stateStack.empty())
		{
			m_stateStack.pop();
			if (!m_stateStack.empty())
			{
				m_stateStack.top()->Resume();
			}
			m_isRemoving = false;
		}

		if (m_isAdding)
		{
			if (!m_stateStack.empty())
			{
				if (m_isReplacing)
				{
					m_stateStack.pop();
				}
				else
				{
					m_stateStack.top()->Pause();
				}
			}

			m_stateStack.push(std::move(m_newState));
			m_stateStack.top()->Init();
			m_isAdding = false;
		}
	}

	StateRef& StateMan::GetCurrentState()
	{
		return m_stateStack.top();
	}
}

