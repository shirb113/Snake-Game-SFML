#pragma once

#include "Game.hpp"
#include "Snake.hpp"

#include <array>
#include<SFML/Graphics.hpp>

class GamePlay : public Engine::State
{
public:
	explicit GamePlay(Game::ContextSharedPtr& context);
	~GamePlay() = default;

public:
	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time delta_time) override;
	void Draw() override;
	void Start() override;
	void Pause() override;

private:
	void set_walls();
	void set_food();
	void set_food_position();
	void set_score();


private:
	Game::ContextSharedPtr _context;
	sf::Sprite _grass;
	sf::Sprite _food;
	std::array<sf::Sprite, 4> _walls;
	Snake _snake;

	sf::Text _score_text;
	uint32_t _score;

	sf::Vector2f _snake_direction;
	sf::Time _elapsed_time;

	bool _is_paused;
};