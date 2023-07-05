#pragma once

#include "Game.hpp"
#include "Snake.hpp"

class GameOver : public Engine::State
{
public:
	explicit GameOver(Game::ContextSharedPtr& context);
	~GameOver() = default;

public:
	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time delta_time) override;
	void Draw() override;

private:
	void set_game_over_title();
	void set_retry_button() ;
	void set_exit_button();

private:
	Game::ContextSharedPtr _context;
	sf::Text _game_over_title;
	sf::Text _retry_button;
	sf::Text _exit_button;

	bool _is_retry_button_selected;
	bool _is_retry_button_pressed;
	bool _is_exit_button_selected;
	bool _is_exit_button_pressed;
	
};