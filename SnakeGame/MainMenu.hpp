#pragma once

#include "State.hpp"
#include "Game.hpp"

#include<SFML/Graphics.hpp>

class MainMenu : public Engine::State
{
public:
	explicit MainMenu(Game::ContextSharedPtr& context);
	~MainMenu() = default;

public:
	 void Init() override;
	 void ProcessInput() override;
	 void Update(sf::Time delta_time) override;
	 void Draw() override;

private:
	void set_game_title();
	void set_play_button();
	void set_exit_button();

private:
	Game::ContextSharedPtr _context;
	sf::Text _game_title;
	sf::Text _play_button;
	sf::Text _exit_button;

	bool _is_play_button_selected;
	bool _is_play_button_pressed;
	bool _is_exit_button_selected;
	bool _is_exit_button_pressed;

};