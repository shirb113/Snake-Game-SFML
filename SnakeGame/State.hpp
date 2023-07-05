#pragma once

#include <SFML/System/Time.hpp>

namespace Engine
{
	class State
	{
	public:
		explicit State() {};
		virtual ~State() {};

		virtual void Init() = 0;
		virtual void ProcessInput() = 0;
		virtual void Update(sf::Time delta_time) = 0;
		virtual void Draw() = 0;

		virtual void Pause() {};
		virtual void Start() {};
	};
}