#pragma once

#include"StateManager.hpp"
#include"AssetManager.hpp"

#include<SFML/Graphics.hpp>

#include<memory>

class GameContext
{
public:
	using AssetManagerPtr = std::unique_ptr<Engine::AssetManager>;
	using StateManagerPtr = std::unique_ptr<Engine::StateManager>;
	using RenderWindowPtr = std::unique_ptr<sf::RenderWindow>;

public:
	explicit GameContext();
	~GameContext() = default;

public:
	AssetManagerPtr _assets;
	StateManagerPtr _states;
	RenderWindowPtr _window;
};