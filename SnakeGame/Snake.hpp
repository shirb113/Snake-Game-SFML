#pragma once

#include <list>

#include<SFML/Graphics.hpp>

class Snake : public sf::Drawable
{
public:
	explicit Snake();
	~Snake() = default;

public:
	void Init(const sf::Texture& texture);
	void Move(const sf::Vector2f& direction);
	bool IsOn(const sf::Sprite& other) const;
	void Grow(const sf::Vector2f& direction);
	bool IsSelfIntersection() const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::list<sf::Sprite> _body;
	std::list<sf::Sprite>::iterator _head;
	std::list<sf::Sprite>::iterator _tail;
};