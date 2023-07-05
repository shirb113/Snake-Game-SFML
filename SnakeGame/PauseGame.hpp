#pragma once

#include "State.hpp"
#include "Game.hpp"

#include<SFML/Graphics.hpp>

class PauseGame : public Engine::State
{
public:
	explicit PauseGame(Game::ContextSharedPtr& context);
	~PauseGame() = default;

public:
	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time delta_time) override;
	void Draw() override;

private:
	Game::ContextSharedPtr _context;
	sf::Text _game_pause_title;
};