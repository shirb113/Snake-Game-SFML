#pragma once

#include "StateManager.hpp"
#include "AssetManager.hpp"
#include "GameContext.hpp"

#include<SFML/Graphics.hpp>

class Game
{
public:
	enum class AssetId 
	{
		MAIN_FONT = 0,
		GRASS,
		FOOD,
		WALL,
		SNAKE,
	};

public:
	using ContextSharedPtr = std::shared_ptr<GameContext>;

public:
	explicit Game();
	~Game() = default;

public:
	void Run();

private:
	ContextSharedPtr _context;
};