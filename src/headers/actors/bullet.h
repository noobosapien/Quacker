#ifndef BULLET_H
#define BULLET_H

class Bullet : public Actor
{
public:
    Bullet(Game *game, Actor *owner, float rotation, double startTime);
    Bullet(Game *game, Actor *owner, glm::vec2 position, float rotation, double startTime);
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

    bool mGo;
    double mStartTime;
    double mShootTime;
    int mId;

    static int mTotalIDs;
};

#endif