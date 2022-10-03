#ifndef RENDERER_H
#define RENDERER_H

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void initialize(int width, int height);
    void deinitialize();
    void setWinDim(int width, int height);

    bool loadShaders();
    bool loadSpriteShader();
    bool loadChargingShader();

    void update();
    class Shader *getShader(const std::string &name);
    void manualDrawTriangles()
    {
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    void insertObject(class RenderComponent *render, unsigned int drawOrder);
    void removeObject(class RenderComponent *render);

    class Camera *getCamera() { return mCamera; }
    class Texture *getTexture(const std::string &filename);

    static int WIN_WIDTH;
    static int WIN_HEIGHT;
    static glm::vec2 WIN_RES;

private:
    std::map<std::string, class Shader *> mShaders;
    std::vector<class RenderComponent *> mRenders;
    std::unordered_map<std::string, Texture *> mTextures;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_GLContext gl_context;

    class Camera *mCamera;
};

#endif