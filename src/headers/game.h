#ifndef GAME_H
#define GAME_H

class Game : public Engine
{
public:
    Game();
    bool initialize();
    void runLoop();
    bool shutDown();
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

    class Player *getPlayer();
    class Enemy *getEnemy();

    class WebsockClient *getWebsocket() { return mWebSocket; }

    static bool DEBUG;

    void setValue(std::string key, std::string value);
    std::string getValue(Globals key);

    void setBullet(class Bullet *bullet, Actor *actor);
    std::vector<Bullet *> &getBullets(Actor *actor);

    void callUIRPC(std::string command);

private:
    void processInput();
    void updateGame() override;
    void generateOutput() override;

    void loadData();
    void unloadData();

    void loadNetwork(int pid, char *name);

    GameState mState;
    bool mConnected;

    std::vector<Actor *> mActors;
    std::vector<Actor *> mPendingActors;
    bool mUpdatingActors;

    class WebsockClient *mWebSocket;

    // game specific
    class Player *mPlayer;
    class Enemy *mEnemy;

    std::map<Globals, std::string> mDataStore;
    std::map<Actor *, std::vector<Bullet *>> mBullets;

    class Utils *mUtils;
};

#endif