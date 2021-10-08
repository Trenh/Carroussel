#include "Game.h"
#include <iostream>

int main(void)
{
    bool isGameInit = Game::instance().initialize();

    if (isGameInit) {
        Game::instance().load();
        Game::instance().loop();
        Game::instance().unload();
    }

    Game::instance().close();

    return 0;
}