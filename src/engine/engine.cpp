#include "../headers/engine/enginepch.h"

Engine::Engine() : mTicksCount(0), mDeltaTime(0.0f), mDebug(false)
{
    mStartTime = std::chrono::high_resolution_clock::now();
    mRenderer = new Renderer();
}

Engine::~Engine()
{
}

void Engine::initialize(int width, int height)
{
    time_t t;
    srand((unsigned)time(&t));
    mRenderer->initialize(width, height);
}

void Engine::shutDown()
{
    SDL_Quit();
}

void Engine::updateGame()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
        ; // 60fps

    mDeltaTime = static_cast<float>(SDL_GetTicks() - mTicksCount) / 1000;

    if (mDeltaTime > 0.05f)
        mDeltaTime = 0.05f;

    mTicksCount = SDL_GetTicks();
}

void Engine::generateOutput()
{
    mRenderer->update();
}

double Engine::getCurrentTime()
{
    auto now = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - mStartTime).count();
    return static_cast<double>(ms);
}