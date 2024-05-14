#pragma once

#include <list>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Snake : public sf::Drawable
{
public:
	Snake();
	~Snake();

	std::list<sf::Sprite>::iterator m_head;
	std::list<sf::Sprite>::iterator m_tail;
	std::list<sf::Sprite> m_body;
	

	void Init(const sf::Texture& texture);
	void Move(const sf::Vector2f& direction);
	void SpecialMove(const sf::Vector2f& direction);
	bool IsOn(const sf::Sprite& other) const;
	void Grow(const sf::Vector2f& direction);
	bool IsSelfCollision() const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};