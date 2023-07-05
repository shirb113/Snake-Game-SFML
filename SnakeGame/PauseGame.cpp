#include "PauseGame.hpp"

PauseGame::PauseGame(Game::ContextSharedPtr& context) :
	_context(context)
{
}

void PauseGame::Init()
{
	_game_pause_title.setFont(_context->_assets->GetFont(static_cast<int>(Game::AssetId::MAIN_FONT)));
	_game_pause_title.setFillColor(sf::Color::Black);
	_game_pause_title.setString("Pause");

	_game_pause_title.setOrigin(_game_pause_title.getLocalBounds().width / 2, _game_pause_title.getLocalBounds().height / 2);
	_game_pause_title.setPosition(_context->_window->getSize().x / 2 - 30.f, _context->_window->getSize().y / 2 - 80.f);
	_game_pause_title.setCharacterSize(50);
}

void PauseGame::ProcessInput()
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
			case sf::Keyboard::Escape:
				_context->_states->PopCurrentStatus();
				break;
			default:
				break;
			}
		}
	}
}

void PauseGame::Update(sf::Time delta_time)
{
	
}

void PauseGame::Draw()
{
	_context->_window->draw(_game_pause_title);
	_context->_window->display();
}
