#include "headers/gamepch.h"

Game::Game() : mPlayer(nullptr), mEnemy(nullptr), mState(EStart)
{
}

bool Game::DEBUG = false;

bool Game::initialize()
{
    Engine::initialize(800, 800);

    return true;
}

void Game::runLoop()
{
    processInput();
    updateGame();
    generateOutput();
}

bool Game::shutDown()
{
    Engine::shutDown();

    return true;
}

void Game::startGame(int pid, char *name, bool left)
{

    if (!mRenderer->loadShaders())
    {
        printf("Failed to load shaders\n");
        return;
    }

    loadData();
    loadNetwork(pid, name);

        mState = EGameplay;
}

// private

void Game::processInput()
{
    SDL_Event event;

    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {

        default:
            break;
        }
    }
}

void Game::updateGame()
{
    Engine::updateGame();

    if (mState == EGameplay)
    {
        if (mConnected)
        {
            mWebSocket->processAllPackets();
            mWebSocket->sendOutgoing();
        }

        // Actor stuff

        mUpdatingActors = true;
        for (auto actor : mActors)
        {
            actor->update(this->mDeltaTime);
        }
        mUpdatingActors = false;

        for (auto pending : mPendingActors)
        {
            pending->computeWorldTransform();
            mActors.emplace_back(pending);
        }
        mPendingActors.clear();

        std::vector<Actor *> deadActors;
        for (auto actor : mActors)
        {
            if (actor->getState() == Actor::EDead)
            {
                deadActors.emplace_back(actor);
            }
        }

        for (auto actor : deadActors)
        {
            delete actor;
        }
    }
}

void Game::generateOutput()
{
    Engine::generateOutput();
}

void Game::loadData()
{
    Actor *temp = new Actor(this);
    new StarBGComponent(temp, mRenderer, mRenderer->getTexture("src/assets/textures/star_07.png"), 100);

    mPlayer = new Player(this);
    mEnemy = new Enemy(this);
    mUtils = new Utils(this);
}

void Game::loadNetwork(int pid, char *name)
{
    mConnected = WebsockClient::staticInit(this, pid, name);
    mWebSocket = WebsockClient::sInstance;
}

void Game::unloadData()
{

    while (!mActors.empty())
    {
        delete mActors.back();
    }

    mDataStore.clear();
    mBullets.clear();

    if (mUtils)
        delete mUtils;
}

void Game::addActor(Actor *actor)
{
    if (mUpdatingActors)
    {
        mPendingActors.emplace_back(actor);
    }
    else
    {
        mActors.emplace_back(actor);
    }
}

void Game::removeActor(Actor *actor)
{
    auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
    if (iter != mPendingActors.end())
    {
        std::iter_swap(iter, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }

    iter = std::find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end())
    {
        std::iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
    }
}

Player *Game::getPlayer()
{
    return mPlayer;
}

Enemy *Game::getEnemy()
{
    return mEnemy;
}

void Game::setValue(std::string key, std::string value)
{

    if (key == "PLAYER_SPEED")
        mDataStore[Globals::GPlayerSpeed] = value;
}

std::string Game::getValue(Globals key)
{
    return mDataStore[key];
}

void Game::setBullet(Bullet *bullet, Actor *actor)
{
    mBullets[actor].push_back(bullet);
}

std::vector<Bullet *> &Game::getBullets(Actor *actor)
{
    return mBullets[actor];
}

void Game::callUIRPC(std::string command)
{
    mUtils->callUIRPC(command);
}
