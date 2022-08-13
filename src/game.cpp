#include "headers/gamepch.h"

Game::Game() : mPlayer(nullptr), mEnemy(nullptr), mLevel(nullptr), mState(EStart), mLeft(true)
{
}

int Game::WIN_WIDTH = 800;
int Game::WIN_HEIGHT = 800;
glm::vec2 Game::WIN_RES = glm::vec2(1.0);

bool Game::initialize()
{
    Engine::initialize(Game::WIN_WIDTH, Game::WIN_HEIGHT);

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
    mLeft = left;

    if (!loadShaders())
    {
        printf("Failed to load shaders\n");
        return;
    }

    loadData();
    loadNetwork(pid, name);

    mState = EGameplay;
}

void Game::setWinDim(int width, int height)
{
    if (height > width)
    {
        Game::WIN_HEIGHT = height;
        Game::WIN_WIDTH = width;
        Game::WIN_RES = glm::vec2(1.0, (float)height / width);

        SDL_SetWindowSize(window, width, height);
        glViewport(-height / 2 + width / 2, 0, height, height);
    }
    else
    {
        Game::WIN_HEIGHT = height;
        Game::WIN_WIDTH = width;
        Game::WIN_RES = glm::vec2((float)width / height, 1.0);

        SDL_SetWindowSize(window, width, height);
        // glViewport(0, -width/2 + height/2, width, width);
        glViewport(0, -width / 2 + height / 2, width, width);
    }
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

    for (auto bg : mBackgrounds)
    {
        bg->draw(mBGShader);
    }

    if (mTilemap)
    {
        // mTilemap->draw(mBGShader);
    }

    for (auto sprite : mSprites)
    {
        sprite->draw(mSpriteShader);
    }

    SDL_GL_SwapWindow(window);
}

void Game::loadData()
{
    mCamera = new Camera();
    Actor *temp = new Actor(this);

    /////////////////////////////////////////////////////////
    BGComponent *bg = new BGComponent(temp, 50);
    // bg->setScreenSize(glm::vec2(2.f, 2.f));

    std::vector<Texture *> bgTexs = {
        getTexture("src/assets/textures/bg3.png"),
        // getTexture("src/assets/textures/bg2.png"),
    };

    // bg->setBGTextures(bgTexs);
    // bg->setScrollSpeed(-.01f);

    // mBackgrounds.push_back(bg);

    bg = new BGComponent(temp, 55);
    bg->setScreenSize(glm::vec2(1.f, 1.5f));

    bgTexs = {
        getTexture("src/assets/textures/bg8.png"),
        // getTexture("src/assets/textures/bg2.png"),
    };

    bg->setBGTextures(bgTexs);
    bg->setScrollSpeed(-.0f);

    // mBackgrounds.push_back(bg);

    // bg = new BGComponent(temp, 56);
    // bg->setScreenSize(glm::vec2(1.f, 1.5f));

    // bgTexs = {
    //     getTexture("src/assets/textures/bg5.png"),
    //     // getTexture("src/assets/textures/bg2.png"),
    // };

    // bg->setBGTextures(bgTexs);
    // bg->setScrollSpeed(-.03f);

    // mBackgrounds.push_back(bg);

    // bg = new BGComponent(temp, 56);
    // bg->setScreenSize(glm::vec2(1.f, 1.5f));

    // bgTexs = {
    //     getTexture("src/assets/textures/bg6.png"),
    //     // getTexture("src/assets/textures/bg2.png"),
    // };

    // bg->setBGTextures(bgTexs);
    // bg->setScrollSpeed(-.04f);

    // mBackgrounds.push_back(bg);
    /////////////////////////////////////////////////////////

    mPlayer = new Player(this, mLeft);
    mEnemy = new Enemy(this, !mLeft);
    mUtils = new Utils(this);
    EM_ASM({UI_RPC("PLAYER_LOST", 'we', 'fe', 20.4)});
    // mLevel = new GameLevel(this);
    // mLevel->load("src/assets/levels/1.txt", 800, 800);
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

    for (auto i : mTextures)
    {
        i.second->unload();
        delete i.second;
    }

    mTextures.clear();
    delete mCamera;

    if (mTilemap)
        removeTilemap(mTilemap);

    if (mLevel)
        delete mLevel; // deleting environment here in the destructor

    mDataStore.clear();

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

void Game::addSprite(SpriteComponent *sprite)
{
    int drawOrder = sprite->getDrawOrder();

    auto iter = mSprites.begin();

    for (; iter != mSprites.end(); ++iter)
    {
        if (drawOrder < (*iter)->getDrawOrder())
            break;
    }
    mSprites.insert(iter, sprite);
}

void Game::removeSprite(SpriteComponent *sprite)
{
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    if (iter != mSprites.end())
    {
        mSprites.erase(iter);
    }
}

void Game::addBG(BGComponent *bg)
{
    mBackgrounds.push_back(bg);
}

void Game::removeBG(BGComponent *bg)
{
    auto iter = std::find(mBackgrounds.begin(), mBackgrounds.end(), bg);
    if (iter != mBackgrounds.end())
    {
        mBackgrounds.erase(iter);
    }
}

Texture *Game::getTexture(const std::string &filename)
{
    Texture *tex = nullptr;

    auto iter = mTextures.find(filename);

    if (iter != mTextures.end())
        tex = iter->second;
    else
    {
        tex = new Texture();

        if (tex->load(filename))
            mTextures.emplace(filename, tex);
        else
        {
            delete tex;
            tex = nullptr;
        }
    }
    return tex;
}

void Game::addTilemap(TilemapComponent *tilemap)
{
    mTilemap = tilemap;
}

void Game::removeTilemap(TilemapComponent *tilemap)
{
    if (mTilemap)
    {
        delete mTilemap;
    }
}

void Game::addEnvironment(class Object *object)
{
    mEnvironment.push_back(object);
}

void Game::removeEnvironment(class Object *object)
{
    auto iter = std::find(mEnvironment.begin(), mEnvironment.end(), object);
    if (iter != mEnvironment.end())
    {
        mEnvironment.erase(iter);
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

std::vector<class Object *> &Game::getEnvironment()
{
    return mEnvironment;
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

void Game::callUIRPC(std::string command)
{
    mUtils->callUIRPC(command);
}

//////////////////////////////////////////////////////////////////////
// SHADERS  ///////////
//////////////////////////////////////////////////////////////////////

bool Game::loadShaders()
{

    if (!loadSpriteShader())
        return false;

    if (!loadBGShader())
        return false;

    return true;
}

bool Game::loadBGShader()
{
    mBGShader = new Shader();

    if (!mBGShader->load("src/shaders/bg.vert", "src/shaders/bg.frag"))
    {
        return false;
    }

    mBGShader->setActive();

    float vertices[] = {
        -1.f, 1.f, 0.f, 0.0f, 1.f,
        1.f, 1.f, 0.f, 1.f, 1.f,
        1.f, -1.f, 0.f, 1.f, 0.f,
        -1.f, -1.f, 0.f, 0.f, 0.f};

    // float vertices[] = {
    //     -1.f, 1.f, 0.f, 0.0f, 1.f,
    //     1.f, 1.f, 0.f, 1.f, 1.f,
    //     1.f, -1.f, 0.f, 1.f, 0.f,
    //     -1.f, -1.f, 0.f, 0.f, 0.f};

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    mBGShader->setVertexData(vertices, 4, indices, 6, 5);

    mBGShader->setAttrib("a_position", 3, 5, 0);
    mBGShader->setAttrib("a_texCoord", 2, 5, 3);

    return true;
}

bool Game::loadSpriteShader()
{
    mSpriteShader = new Shader();

    if (!mSpriteShader->load("src/shaders/sprite.vert", "src/shaders/sprite.frag"))
    {
        return false;
    }

    mSpriteShader->setActive();

    float vertices[] = {
        -1.f, 1.f, 0.f, 0.f, 1.f,
        1.f, 1.f, 0.f, 1.f, 1.f,
        1.f, -1.f, 0.f, 1.f, 0.f,
        -1.f, -1.f, 0.f, 0.f, 0.f};

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    mSpriteShader->setVertexData(vertices, 4, indices, 6, 5);

    mSpriteShader->setAttrib("a_position", 3, 5, 0);
    mSpriteShader->setAttrib("a_texCoord", 2, 5, 3);

    return true;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////