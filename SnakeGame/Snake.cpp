#include "Snake.hpp"

#define PIXEL_SIZE 32.f

Snake::Snake():
	_body(std::list<sf::Sprite>(4))
{
	_head = --_body.end();
	_tail = _body.begin();
}

void Snake::Init(const sf::Texture& texture)
{
	float pixel = PIXEL_SIZE;
	for (auto& piece : _body)
	{
		piece.setTexture(texture);
		piece.setPosition({pixel, PIXEL_SIZE });
		pixel += PIXEL_SIZE;
	}
}

void Snake::Move(const sf::Vector2f& direction)
{
	_tail->setPosition(_head->getPosition() + direction);
	_head = _tail;
	++_tail;

	if (_tail == _body.end())
	{
		_tail = _body.begin();
	}
}

bool Snake::IsOn(const sf::Sprite& other) const
{
	return other.getGlobalBounds().intersects(_head->getGlobalBounds());
}

void Snake::Grow(const sf::Vector2f& direction)
{
	sf::Sprite new_piece;
	new_piece.setTexture(*(_body.begin()->getTexture()));
	new_piece.setPosition(_head->getPosition() + direction);

	_head = _body.insert(++_head, new_piece);

}

bool Snake::IsSelfIntersection() const
{
	bool flag = false;

	for (auto piece = _body.begin(); piece != _body.end(); ++piece)
	{
		if (_head != piece)
		{
			flag = IsOn(*piece);

			if (flag)
			{
				break;
			}
		}
	}

	return flag;
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& piece : _body)
	{
		target.draw(piece);
	}
}
