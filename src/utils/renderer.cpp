#include "../headers/gamepch.h"

int Renderer::WIN_WIDTH = 800;
int Renderer::WIN_HEIGHT = 800;
glm::vec2 Renderer::WIN_RES = glm::vec2(1.0);

Renderer::Renderer() : mCamera(nullptr), mFBO(nullptr)
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
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);

    gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    glViewport(0, 0, width, height);

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);
    glDepthMask(GL_TRUE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    mFBO = new Framebuffer(this);
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
        Renderer::WIN_RES = glm::vec2((float)height);

        SDL_SetWindowSize(window, width, height);
        glViewport(-height / 2 + width / 2, 0, height, height);
    }
    else
    {
        Renderer::WIN_HEIGHT = height;
        Renderer::WIN_WIDTH = width;
        Renderer::WIN_RES = glm::vec2((float)width);

        SDL_SetWindowSize(window, width, height);
        glViewport(0, -width / 2 + height / 2, width, width);
    }

    if (mFBO)
        mFBO->resizeTexture();
}

void Renderer::update()
{
    if (mFBO)
    {
        mFBO->bind();
        glEnable(GL_DEPTH_TEST);
    }

    glClearColor(0.196, 0.161, 0.278, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto obj : mRenders)
    {
        obj->draw();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    if (mFBO)
    {
        mFBO->unbind();
        mFBO->draw();
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

    if (!loadLightningShader())
        return false;

    if (!loadCircleDebugShader())
        return false;

    if (!loadFramebufferShader())
        return false;

    if (!loadHPViewShader())
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

    mSpriteShader->setVertexData(true, vertices, 4, indices, 6, 5);

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

    mChargingShader->setVertexData(true, vertices, 4, indices, 6, 5);

    mChargingShader->setAttrib("a_position", 3, 5, 0);
    mChargingShader->setAttrib("a_texCoord", 2, 5, 3);

    mShaders["charging"] = mChargingShader;

    return true;
}

bool Renderer::loadLightningShader()
{
    auto mLightningShader = new Shader();

    if (!mLightningShader->load("src/shaders/lightning.vert", "src/shaders/lightning.frag"))
    {
        return false;
    }

    mLightningShader->setActive();

    float vertices[] = {
        -1.f, 1.f, 0.f, 0.f, 1.f,
        1.f, 1.f, 0.f, 1.f, 1.f,
        1.f, -1.f, 0.f, 1.f, 0.f,
        -1.f, -1.f, 0.f, 0.f, 0.f};

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    mLightningShader->setVertexData(true, vertices, 4, indices, 6, 5);

    mLightningShader->setAttrib("a_position", 3, 5, 0);
    mLightningShader->setAttrib("a_texCoord", 2, 5, 3);

    mShaders["lightning"] = mLightningShader;

    return true;
}

bool Renderer::loadCircleDebugShader()
{
    auto mCircelDebugShader = new Shader();

    if (!mCircelDebugShader->load("src/shaders/circledebug.vert", "src/shaders/circledebug.frag"))
    {
        return false;
    }

    mCircelDebugShader->setActive();

    float vertices[] = {
        -1.f, 1.f, 0.f,
        1.f, 1.f, 0.f,
        1.f, -1.f, 0.f,
        -1.f, -1.f, 0.f};

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    mCircelDebugShader->setVertexData(true, vertices, 4, indices, 6, 3);

    mCircelDebugShader->setAttrib("a_position", 3, 3, 0);

    mShaders["circledebug"] = mCircelDebugShader;

    return true;
}

bool Renderer::loadFramebufferShader()
{
    auto mFramebufferShader = new Shader();

    if (!mFramebufferShader->load("src/shaders/framebuffer.vert", "src/shaders/framebuffer.frag"))
    {
        return false;
    }

    mFramebufferShader->setActive();

    float vertices[] = {
        -1.f, 1.f, 0.f, 0.f, 1.f,
        1.f, 1.f, 0.f, 1.f, 1.f,
        1.f, -1.f, 0.f, 1.f, 0.f,
        -1.f, -1.f, 0.f, 0.f, 0.f};

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    mFramebufferShader->setVertexData(true, vertices, 4, indices, 6, 5);

    mFramebufferShader->setAttrib("a_position", 2, 5, 0);
    mFramebufferShader->setAttrib("a_texCoord", 2, 5, 3);

    mShaders["framebuffer"] = mFramebufferShader;

    if (mFBO)
        mFBO->attachShader();

    return true;
}

bool Renderer::loadHPViewShader()
{
    auto mHPViewShader = new Shader();

    if (!mHPViewShader->load("src/shaders/health.vert", "src/shaders/health.frag"))
    {
        return false;
    }

    mHPViewShader->setActive();

    float vertices[] = {
        -1.f, 1.f, 0.f,
        1.f, 1.f, 0.f,
        1.f, -1.f, 0.f,
        -1.f, -1.f, 0.f};

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    mHPViewShader->setVertexData(true, vertices, 4, indices, 6, 3);

    mHPViewShader->setAttrib("a_position", 3, 3, 0);

    mShaders["health"] = mHPViewShader;

    return true;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////