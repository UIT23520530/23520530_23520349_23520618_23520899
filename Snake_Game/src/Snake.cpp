#include <Snake.hpp>
#include <DEFINITIONS.hpp>

Snake::Snake() : m_body(std::list<sf::Sprite>(3))
{
	m_head = --m_body.end(); // m_head = end - 1
	m_tail = m_body.begin(); // m_tail = begin
}

Snake::~Snake()
{

}

void Snake::Init(const sf::Texture& texture)
{
	float X = 64.f;
	for (auto& body : m_body)
	{
		body.setTexture(texture);
		body.setPosition({ X, 64.f });
		X += 16.f;
	}
}

void Snake::Move(const sf::Vector2f& direction)
{
	m_tail->setPosition(m_head->getPosition() + direction);
	m_head = m_tail;
	++m_tail;

	if (m_tail == m_body.end())
	{
		m_tail = m_body.begin();
	}
}

void Snake::SpecialMove(const sf::Vector2f& direction)
{
	if (direction == sf::Vector2f(16.f, 0.f))
	{
		m_head->setPosition(sf::Vector2f(0.f, m_head->getPosition().y));
	}
	else if (direction == sf::Vector2f(-16.f, 0.f))
	{
		m_head->setPosition(sf::Vector2f(GAME_FRAME_WIDTH - 16, m_head->getPosition().y));
	}
	else if (direction == sf::Vector2f(0.f, -16.f))
	{
		m_head->setPosition(sf::Vector2f(m_head->getPosition().x, GAME_FRAME_HEIGHT - 16));
	}
	else if (direction == sf::Vector2f(0.f, 16.f))
	{
		m_head->setPosition(sf::Vector2f(m_head->getPosition().x, 0.f));
	}

}

bool Snake::IsOn(const sf::Sprite& other) const
{
	return other.getGlobalBounds().intersects(m_head->getGlobalBounds());
}

bool Snake::IsSelfCollision() const
{
	for (auto body = m_body.begin(); body != m_head; ++body)
	{
		if (IsOn(*body))
		{
			return true;
		}
	}
	return false;
}

void Snake::Grow(const sf::Vector2f& direction)
{
	sf::Sprite newBody;
	newBody.setTexture(*(m_body.begin()->getTexture()));
	newBody.setPosition(m_head->getPosition() + direction);
	
	m_head = m_body.insert(++m_head, newBody);
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& body : m_body)
	{
		target.draw(body);
	}
}
