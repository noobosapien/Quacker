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

private:
    Actor *mBulletOwner;
    bool mGo;
    double mStartTime;
    double mShootTime;
};

#endif