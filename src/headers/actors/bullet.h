#ifndef BULLET_H
#define BULLET_H

class Bullet : public Actor
{
public:
    enum Type
    {
        BULLET,
        LIGHTNING
    };

    Bullet(Game *game, Actor *owner, Type type, float rotation, double startTime);
    Bullet(Game *game, Actor *owner, Type type, glm::vec2 position, float rotation, double startTime);
    ~Bullet();

    void updateActor(float delta) override;

    virtual void writePacket(OutputStream *out) override;
    inline int getID() { return mId; }

    inline class CollisionComponent *getCollider() { return mCollider; }

    // copy assignment for vector erase use

    Bullet &operator=(const Bullet &bullet);
    friend bool operator==(const Bullet b1, const Bullet b2);

private:
    Actor *mBulletOwner;
    class CollisionComponent *mCollider;
    class SpriteComponent *mSprite;

    Type mType;

    bool mGo;
    double mStartTime;
    double mShootTime;
    int mId;

    static int mTotalIDs;
};

#endif