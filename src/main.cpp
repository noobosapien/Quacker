#include "./headers/gamepch.h"

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
    game->setWinDim(width, height);
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

// template <typename T, typename... Types>
// void printC(int n, ...)
// {
//     std::cout << "Here" << std::endl;
// }

// EMSCRIPTEN_BINDINGS(rpc)
// {
//     emscripten::function("printC", &printC);
// }

extern "C"
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_KEEPALIVE
#endif

    void
    call_rpc(float vals[], int size)
{
    float res = 0;
    for (int i = 0; i < size; i++)
        std::cout << res << std::endl;
}

// float call_rpc(int n, ...)
// {
//     va_list ptr;
//     va_start(ptr, n);

//     for (int i = 0; i < n; i++)
//     {
//         int tmp = va_arg(ptr, int);
//         printf("here var: %c\n", tmp);
//     }

//     va_end(ptr);

//     return 1.f;
// }

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