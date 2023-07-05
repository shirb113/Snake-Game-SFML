#include "MainMenu.hpp"
#include "GamePlay.hpp"

MainMenu::MainMenu(Game::ContextSharedPtr& context) :
	_context(context),
	_is_play_button_selected(true),
	_is_play_button_pressed(false),
	_is_exit_button_selected(false),
	_is_exit_button_pressed(false)
{
}

void MainMenu::Init()
{
	set_game_title();
	set_play_button();
	set_exit_button();
}

void MainMenu::ProcessInput()
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
				if (!_is_play_button_selected)
				{
					_is_play_button_selected = true;
					_is_exit_button_selected = false;
				}
				break;

			case sf::Keyboard::Down:
				if (!_is_exit_button_selected)
				{
					_is_exit_button_selected = true;
					_is_play_button_selected = false;
				}
				break;
			
			case sf::Keyboard::Return:
				_is_play_button_pressed = false;
				_is_exit_button_pressed = false;

				if (_is_play_button_selected)
				{
					_is_play_button_pressed = true;
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

void MainMenu::Update(sf::Time delta_time)
{
	if (_is_play_button_selected)
	{
		_play_button.setFillColor(sf::Color::White);
		_exit_button.setFillColor(sf::Color::Black);
	}
	else 
	{
		_exit_button.setFillColor(sf::Color::White);
		_play_button.setFillColor(sf::Color::Black);
	}

	if (_is_play_button_pressed)
	{
		_context->_states->Add(std::make_unique<GamePlay>(_context), true);
	}
	else if (_is_exit_button_pressed)
	{
		_context->_window->close();
	}
}

void MainMenu::Draw()
{
	_context->_window->clear(sf::Color(50, 168, 82));
	_context->_window->draw(_game_title);
	_context->_window->draw(_play_button);
	_context->_window->draw(_exit_button);
	_context->_window->display();
}

void MainMenu::set_game_title()
{
	_context->_assets->AddFont(static_cast<int>(Game::AssetId::MAIN_FONT), "assets\\Pacifico-Regular.ttf");
	_game_title.setFont(_context->_assets->GetFont(static_cast<int>(Game::AssetId::MAIN_FONT)));
	_game_title.setString("Snake Game");
	_game_title.setFillColor(sf::Color::Black);
	_game_title.setCharacterSize(50);

	_game_title.setOrigin(_game_title.getLocalBounds().width / 2, _game_title.getLocalBounds().height / 2);

	_game_title.setPosition(_context->_window->getSize().x / 2, _context->_window->getSize().y / 2 - 150.f);
}

void MainMenu::set_play_button()
{
	_play_button.setFont(_context->_assets->GetFont(static_cast<int>(Game::AssetId::MAIN_FONT)));
	_play_button.setString("Play");

	_play_button.setOrigin(_play_button.getLocalBounds().width / 2,_play_button.getLocalBounds().height / 2);

	_play_button.setPosition(_context->_window->getSize().x / 2,_context->_window->getSize().y / 2 - 35.f);
	_play_button.setCharacterSize(30);
}

void MainMenu::set_exit_button()
{
	_exit_button.setFont(_context->_assets->GetFont(static_cast<int>(Game::AssetId::MAIN_FONT)));
	_exit_button.setString("Exit");

	_exit_button.setOrigin(_exit_button.getLocalBounds().width / 2, _exit_button.getLocalBounds().height / 2);

	_exit_button.setPosition(_context->_window->getSize().x / 2, _context->_window->getSize().y / 2 + 35.f);
	_exit_button.setCharacterSize(30);
}
