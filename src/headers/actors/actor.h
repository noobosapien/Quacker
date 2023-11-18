#ifndef ACTOR_H
#define ACTOR_H

class Actor
{
public:
    enum State
    {
        EActive,
        EPaused,
        EDead
    };

    Actor(class Game *game);
    virtual ~Actor();

    void update(float delta);
    void updateComponents(float delta);
    virtual void updateActor(float delta);

    void processInput(SDL_Event &event);
    virtual void actorInput(const SDL_Event &event);

    inline void setPosition(const glm::vec3 &pos)
    {
        mPosition = pos;
        mRecomputeWorldTransform = true;
    }
    inline const glm::vec3 &getPosition() { return mPosition; }
    inline void setScale(float scale)
    {
        mScale = scale;
        mRecomputeWorldTransform = true;
    }
    inline const float getScale() { return mScale; }
    inline void setRotation(float rotation)
    {
        mRotation = rotation;
        mRecomputeWorldTransform = true;
    }
    inline const float getRotation() { return mRotation; }

    void computeWorldTransform();
    inline const glm::mat4 &getWorldTransform() { return mWorldTransform; }

    glm::vec3 getForward() { return glm::vec3(glm::cos(glm::radians(mRotation)), glm::sin(glm::radians(mRotation)), 0.0); }

    State getState() { return mState; }
    void setState(State state) { mState = state; }

    class Game *getGame() { return mGame; }

    void addComponent(class Component *component);
    void removeComponent(class Component *component);

    virtual void writePacket(class OutputStream *out){};

private:
    State mState;
    glm::vec3 mPosition;
    glm::mat4 mWorldTransform;
    float mScale;
    float mRotation;
    bool mRecomputeWorldTransform;
    class Game *mGame;

    std::vector<class Component *> mComponents;
};

#endif