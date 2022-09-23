#ifndef ENGINE_H
#define ENGINE_H

class Engine
{
public:
    friend class Game;

    Engine();
    virtual ~Engine();

    void initialize(int width, int height);
    void shutDown();

    void setDebug(bool value) { mDebug = value; }

    double getCurrentTime();
    class Renderer *getRenderer() { return mRenderer; }

protected:
    virtual void updateGame();
    virtual void generateOutput();

    class Renderer *mRenderer;

    bool mDebug;

    Uint32 mTicksCount;
    float mDeltaTime;

    std::chrono::high_resolution_clock::time_point mStartTime;

private:
};

#endif