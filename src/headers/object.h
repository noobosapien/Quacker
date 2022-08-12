#ifndef OBJECT_H
#define OBJECT_H

enum class TYPE
{
    TYPE_1,
    TYPE_2,
    TYPE_3
};

class Object : public Actor
{
public:
    Object(Game *game, GameLevel *level, glm::vec2 pos, float scale, TYPE type);
    ~Object();

    void updateActor(float delta) override;
    class CollisionComponent *getCollider() { return mCollider; }
    unsigned int getID() { return mID; }

private:
    class CollisionComponent *mCollider;
    unsigned int mID;

    static unsigned int getNewID();
    static unsigned int mLastID;
};

#endif