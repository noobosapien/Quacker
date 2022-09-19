#ifndef GAME_H
#define GAME_H

class Game : public Engine
{
public:
    Game();
    bool initialize();
    void runLoop();
    bool shutDown();
    void setWinDim(int width, int height);
    void startGame(int pid, char *name, bool left);

    enum GameState
    {
        EStart,
        EGameplay,
        EPause
    };

    enum Globals
    {
        GPlayerSpeed
    };

    void addActor(Actor *actor);
    void removeActor(Actor *actor);

    void addSprite(SpriteComponent *sprite);
    void removeSprite(SpriteComponent *sprite);

    class Player *getPlayer();
    class Enemy *getEnemy();

    Texture *getTexture(const std::string &filename);
    Camera *getCamera() { return mCamera; }
    class WebsockClient *getWebsocket() { return mWebSocket; }

    static int WIN_WIDTH;
    static int WIN_HEIGHT;
    static glm::vec2 WIN_RES;
    static bool DEBUG;

    void setValue(std::string key, std::string value);
    std::string getValue(Globals key);

    void callUIRPC(std::string command);

private:
    void processInput();
    void updateGame() override;
    void generateOutput() override;

    void loadData();
    void unloadData();

    void loadNetwork(int pid, char *name);

    bool loadShaders();
    bool loadSpriteShader();

    GameState mState;
    bool mConnected;

    std::vector<Actor *> mActors;
    std::vector<Actor *> mPendingActors;
    bool mUpdatingActors;

    std::vector<SpriteComponent *> mSprites;
    std::unordered_map<std::string, Texture *> mTextures;
    Camera *mCamera;

    class WebsockClient *mWebSocket;

    // shaders
    Shader *mSpriteShader;

    // game specific
    class Player *mPlayer;
    class Enemy *mEnemy;

    std::map<Globals, std::string> mDataStore;

    class Utils *mUtils;
};

#endif