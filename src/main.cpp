#include "headers/gamepch.h"

static Game *game;

void loop()
{
    game->runLoop();
}

extern "C"
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_KEEPALIVE
#endif

    void
    set_win_dim(int width, int height)
{
    game->getRenderer()->setWinDim(width, height);
}

extern "C"
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_KEEPALIVE
#endif

    void
    start_game(int pid, char *name, bool left)
{
    std::cout << name << left << std::endl;
    game->startGame(pid, name, left);
}

extern "C"
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_KEEPALIVE
#endif

    void
    set_game_data(char *key, char *value)
{
    game->setValue(std::string(key), std::string(value));
}

extern "C"
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_KEEPALIVE
#endif

    void
    call_ui_rpc(char *command)
{
    game->callUIRPC(std::string(command));
}

int main()
{
    game = new Game;

    bool success = game->initialize();

    if (success)
    {
        emscripten_set_main_loop(loop, 0, 0);
        // game->startGame();
    }
    else
        delete game;

    return 0;
}