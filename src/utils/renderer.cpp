#include "../headers/gamepch.h"

int Renderer::WIN_WIDTH = 800;
int Renderer::WIN_HEIGHT = 800;
glm::vec2 Renderer::WIN_RES = glm::vec2(1.0);

Renderer::Renderer() : mCamera(nullptr)
{
}

Renderer::~Renderer()
{
}

void Renderer::initialize(int width, int height)
{
    if (mCamera == nullptr)
    {
        mCamera = new Camera;
    }

    SDL_Init(SDL_INIT_VIDEO);

    // Enable double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // Force OpenGL to use hardware acceleration
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);

    gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);

    glViewport(0, 0, width, height);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::deinitialize()
{
    for (auto i : mTextures)
    {
        i.second->unload();
        delete i.second;
    }

    mTextures.clear();
    delete mCamera;
}

void Renderer::setWinDim(int width, int height)
{
    if (height > width)
    {
        Renderer::WIN_HEIGHT = height;
        Renderer::WIN_WIDTH = width;
        Renderer::WIN_RES = glm::vec2(1.0, (float)height / width);

        SDL_SetWindowSize(window, width, height);
        glViewport(-height / 2 + width / 2, 0, height, height);
    }
    else
    {
        Renderer::WIN_HEIGHT = height;
        Renderer::WIN_WIDTH = width;
        Renderer::WIN_RES = glm::vec2((float)width / height, 1.0);

        SDL_SetWindowSize(window, width, height);
        // glViewport(0, -width/2 + height/2, width, width);
        glViewport(0, -width / 2 + height / 2, width, width);
    }
}

void Renderer::update()
{
    glClearColor(0.196, 0.161, 0.278, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (auto obj : mRenders)
    {
        obj->draw();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    SDL_GL_SwapWindow(window);
}

Shader *Renderer::getShader(const std::string &name)
{
    if (mShaders[name])
        return mShaders[name];

    return nullptr;
}

Texture *Renderer::getTexture(const std::string &filename)
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

void Renderer::insertObject(class RenderComponent *render, unsigned int drawOrder)
{
    auto iter = mRenders.begin();

    for (; iter != mRenders.end(); ++iter)
    {
        if (drawOrder < (*iter)->getDrawOrder())
            break;
    }
    mRenders.insert(iter, render);
}

void Renderer::removeObject(class RenderComponent *render)
{
    auto iter = std::find(mRenders.begin(), mRenders.end(), render);
    if (iter != mRenders.end())
    {
        mRenders.erase(iter);
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

bool Renderer::loadShaders()
{
    if (!loadSpriteShader())
        return false;

    if (!loadChargingShader())
        return false;

    return true;
}

bool Renderer::loadSpriteShader()
{
    auto mSpriteShader = new Shader();

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

    mShaders["sprite"] = mSpriteShader;

    return true;
}

bool Renderer::loadChargingShader()
{
    auto mChargingShader = new Shader();

    if (!mChargingShader->load("src/shaders/charging.vert", "src/shaders/charging.frag"))
    {
        return false;
    }

    mChargingShader->setActive();

    float vertices[] = {
        -1.f, 1.f, 0.f, 0.f, 1.f,
        1.f, 1.f, 0.f, 1.f, 1.f,
        1.f, -1.f, 0.f, 1.f, 0.f,
        -1.f, -1.f, 0.f, 0.f, 0.f};

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    mChargingShader->setVertexData(vertices, 4, indices, 6, 5);

    mChargingShader->setAttrib("a_position", 3, 5, 0);
    mChargingShader->setAttrib("a_texCoord", 2, 5, 3);

    mShaders["charging"] = mChargingShader;

    return true;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////