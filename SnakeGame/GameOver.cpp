#include "GameOver.hpp"
#include "GamePlay.hpp"

GameOver::GameOver(Game::ContextSharedPtr& context) :
	_context(context),
	_is_retry_button_selected(true),
	_is_retry_button_pressed(false),
	_is_exit_button_selected(false),
	_is_exit_button_pressed(false)
{
}

void GameOver::Init()
{
	set_game_over_title();
	set_retry_button();
	set_exit_button();
}

void GameOver::ProcessInput()
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
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				if (!_is_retry_button_selected)
				{
					_is_retry_button_selected = true;
					_is_exit_button_selected = false;
				}
				break;

			case sf::Keyboard::Down:
				if (!_is_exit_button_selected)
				{
					_is_exit_button_selected = true;
					_is_retry_button_selected = false;
				}
				break;

			case sf::Keyboard::Return:
				_is_retry_button_pressed = false;
				_is_exit_button_pressed = false;

				if (_is_retry_button_selected)
				{
					_is_retry_button_pressed = true;
				}
				else
				{
					_is_exit_button_pressed = true;
				}
				break;

			default:
				break;
			}
		}
	}
}

void GameOver::Update(sf::Time delta_time)
{
	if (_is_retry_button_selected)
	{
		_retry_button.setFillColor(sf::Color::Black);
		_exit_button.setFillColor(sf::Color::White);
	}
	else
	{
		_exit_button.setFillColor(sf::Color::Black);
		_retry_button.setFillColor(sf::Color::White);
	}

	if (_is_retry_button_pressed)
	{
		_context->_states->Add(std::make_unique<GamePlay>(_context), true);
	}
	else if (_is_exit_button_pressed)
	{
		_context->_window->close();
	}
}

void GameOver::Draw()
{
	_context->_window->clear(sf::Color::Red);
	_context->_window->draw(_game_over_title);
	_context->_window->draw(_retry_button);
	_context->_window->draw(_exit_button);
	_context->_window->display();
}

void GameOver::set_game_over_title()
{
	_game_over_title.setFont(_context->_assets->GetFont(static_cast<int>(Game::AssetId::MAIN_FONT)));
	_game_over_title.setString("Game Over");

	_game_over_title.setOrigin(_game_over_title.getLocalBounds().width / 2, _game_over_title.getLocalBounds().height / 2);

	_game_over_title.setPosition(_context->_window->getSize().x / 2 - 60.f, _context->_window->getSize().y / 2 - 150.f);
	_game_over_title.setCharacterSize(50);
}

void GameOver::set_retry_button()
{
	_retry_button.setFont(_context->_assets->GetFont(static_cast<int>(Game::AssetId::MAIN_FONT)));
	_retry_button.setString("Retry");

	_retry_button.setOrigin(_retry_button.getLocalBounds().width / 2, _retry_button.getLocalBounds().height / 2);

	_retry_button.setPosition(_context->_window->getSize().x / 2, _context->_window->getSize().y / 2 - 35.f);
	_retry_button.setCharacterSize(30);
}

void GameOver::set_exit_button()
{
	_exit_button.setFont(_context->_assets->GetFont(static_cast<int>(Game::AssetId::MAIN_FONT)));
	_exit_button.setString("Exit");

	_exit_button.setOrigin(_exit_button.getLocalBounds().width / 2, _exit_button.getLocalBounds().height / 2);

	_exit_button.setPosition(_context->_window->getSize().x / 2, _context->_window->getSize().y / 2 + 35.f);
	_exit_button.setCharacterSize(30);
}
