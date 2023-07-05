#include "Game.hpp"
#include "MainMenu.hpp"

#define width 640*2
#define hight 352*2

Game::Game():
    _context(std::make_shared<GameContext>())
{
	_context->_window->create(sf::VideoMode(width, hight), "Snake Game", sf::Style::Close);
    _context->_states->Add(std::make_unique<MainMenu>(_context));
}

void Game::Run()
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock clock;
    sf::Time time_since_last_frame = sf::Time::Zero;

    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);

    while (_context->_window->isOpen())
    {
        time_since_last_frame += clock.restart();

        while (time_since_last_frame > TIME_PER_FRAME)
        {
            time_since_last_frame -= TIME_PER_FRAME;

            _context->_states->ProcessStateChange();
            _context->_states->GetCurrentState()->ProcessInput();
            _context->_states->GetCurrentState()->Update(TIME_PER_FRAME);
            _context->_states->GetCurrentState()->Draw();
        } 
    }
}
