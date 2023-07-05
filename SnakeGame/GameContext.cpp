#include "GameContext.hpp"

GameContext::GameContext() :
	_assets(std::make_unique<Engine::AssetManager>()),
	_states(std::make_unique<Engine::StateManager>()),
	_window(std::make_unique<sf::RenderWindow>())
{
}


