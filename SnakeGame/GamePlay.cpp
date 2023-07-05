#include "GamePlay.hpp"
#include "GameOver.hpp"
#include "PauseGame.hpp"

#include <stdlib.h>
#include <time.h>

#define PIXEL_SIZE 32.f

GamePlay::GamePlay(Game::ContextSharedPtr& context) :
	_context(context),
	_snake(),
	_snake_direction({ PIXEL_SIZE,0.f}),
	_elapsed_time(sf::Time::Zero),
	_score(0),
	_is_paused(false)
{
	srand(time(nullptr));
}

void GamePlay::Init()
{
	_context->_assets->AddTexture(static_cast<int>(Game::AssetId::GRASS), "assets\\green.png", true);
	_context->_assets->AddTexture(static_cast<int>(Game::AssetId::SNAKE), "assets\\big_blue.png");

	_grass.setTexture(_context->_assets->GetTexture(static_cast<int>(Game::AssetId::GRASS)));
	_grass.setTextureRect(_context->_window->getViewport(_context->_window->getDefaultView()));

	set_walls();
	set_food();
	set_score();

	_snake.Init(_context->_assets->GetTexture(static_cast<int>(Game::AssetId::SNAKE)));
}

void GamePlay::ProcessInput()
{
	sf::Event event;
	while (_context->_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_context->_window->close();
		}

		else if (event.type == sf::Event::KeyPressed)
		{
			sf::Vector2f new_direction = _snake_direction;
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				new_direction = { 0.f,-PIXEL_SIZE };
				break;

			case sf::Keyboard::Down:
				new_direction = { 0.f,PIXEL_SIZE };
				break;

			case sf::Keyboard::Right:
				new_direction = { PIXEL_SIZE,0.f };
				break;
			
			case sf::Keyboard::Left:
				new_direction = { -PIXEL_SIZE,0.f };
				break;
			case sf::Keyboard::Escape:
				_context->_states->Add(std::make_unique<PauseGame>(_context));
				break;

			default:
				break;
			}

			if ((std::abs(_snake_direction.x) != std::abs(new_direction.x)) ||
				(std::abs(_snake_direction.y) != std::abs(new_direction.y)))
			{
				_snake_direction = new_direction;
			}
		}
	}
}

void GamePlay::Update(sf::Time delta_time)
{
	if (_is_paused)
	{
		return;
	}

	_elapsed_time += delta_time;

	if (_elapsed_time.asSeconds() > 0.1)
	{
		for (auto& wall : _walls)
		{
			if (_snake.IsOn(wall))
			{
				_context->_states->Add(std::make_unique<GameOver>(_context), true);
				break;
			}
		}

		if (_snake.IsOn(_food))
		{
			_snake.Grow(_snake_direction);
			set_food_position();
			
			_score += 1;
			_score_text.setString("Score :  " + std::to_string(_score));
		}
		else
		{
			_snake.Move(_snake_direction);
		}

		if (_snake.IsSelfIntersection())
		{
			_context->_states->Add(std::make_unique<GameOver>(_context), true);
		}

		_elapsed_time = sf::Time::Zero;
	}
}

void GamePlay::Draw()
{
	_context->_window->clear(sf::Color::Black);
	_context->_window->draw(_grass);

	for (auto& wall : _walls)
	{
		_context->_window->draw(wall);
	}
	_context->_window->draw(_food);
	_context->_window->draw(_snake);
	_context->_window->draw(_score_text);
	_context->_window->display();
}

void GamePlay::Start()
{
	_is_paused = false;
}

void GamePlay::Pause()
{
	_is_paused = true;
}

void GamePlay::set_walls()
{
	_context->_assets->AddTexture(static_cast<int>(Game::AssetId::WALL), "assets\\green.png", true);

	for (auto& wall : _walls)
	{
		wall.setTexture(_context->_assets->GetTexture(static_cast<int>(Game::AssetId::WALL)));
	}

	int pixel_size = static_cast<int>(PIXEL_SIZE);
	_walls[0].setTextureRect({ 0,0,static_cast<int>(_context->_window->getSize().x), pixel_size });
	_walls[1].setTextureRect({ 0,0,static_cast<int>(_context->_window->getSize().x), pixel_size });
	_walls[1].setPosition(0, static_cast<int>(_context->_window->getSize().y) - pixel_size);

	_walls[2].setTextureRect({ 0,0, pixel_size, static_cast<int>(_context->_window->getSize().y) });
	_walls[3].setTextureRect({ 0,0, pixel_size, static_cast<int>(_context->_window->getSize().y) });
	_walls[3].setPosition(static_cast<int>(_context->_window->getSize().x) - pixel_size, 0);
}

void GamePlay::set_food()
{
	_context->_assets->AddTexture(static_cast<int>(Game::AssetId::FOOD), "assets\\big_food.png");

	_food.setTexture(_context->_assets->GetTexture(static_cast<int>(Game::AssetId::FOOD)));

	set_food_position();
}

void GamePlay::set_food_position()
{
	int x = 0; int y = 0;
	x = std::clamp<int>(rand() % _context->_window->getSize().x, PIXEL_SIZE, _context->_window->getSize().x - 2 * PIXEL_SIZE);
	y = std::clamp<int>(rand() % _context->_window->getSize().y, PIXEL_SIZE, _context->_window->getSize().y - 2 * PIXEL_SIZE);

	_food.setPosition(x, y);
}

void GamePlay::set_score()
{
	_score_text.setFont(_context->_assets->GetFont(static_cast<int>(Game::AssetId::MAIN_FONT)));
	_score_text.setFillColor(sf::Color::Black);
	_score_text.setString("Score :  " + std::to_string(_score));
}
