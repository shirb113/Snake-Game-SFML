#include "Game.hpp"

#include <windows.h>


int WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    Game game;
    game.Run();

    return 0;
}