void GamePlay::Update(const sf::Time &deltaTime)
{
	if (!m_isPaused)
	{
		m_elapsedTime += deltaTime;
		if (m_elapsedTime.asSeconds()>0.1)
		{
			for (auto& wall : m_walls)
			{
				if (m_snake.IsOn(wall))
				{
					m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
					break;
				}
			}
			if (m_snake.IsOn(m_food))
			{
				m_snake.Grow(m_snakeDirection);
				int x = 0, y = 0;
				x = std::clamp<int>(rand() % m_context->m_window->getSize().x, 16, m_context->m_window->getSize().x - 2 * 16);
				y = std::clamp<int>(rand() % m_context->m_window->getSize().y, 16, m_context->m_window->getSize().y - 2 * 16);
				m_food.setPosition(x, y);
				m_score += 1;
				m_scoreText.setString("Score : " + std::to_string(m_score));
			}
			else
			{
				m_snake.Move(m_snakeDirection);
			}

			if (m_snake.IsSelfIntersecting())
			{
				m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
			}

			m_elapsedTime = sf::Time::Zero;
		}
	}
}
