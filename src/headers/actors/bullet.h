#ifndef BULLET_H
#define BULLET_H

class Bullet : public Actor
{
public:
    Bullet(Game *game, Actor *owner, glm::vec2 forward);
    ~Bullet();

    void updateActor(float delta) override;

    virtual glm::vec2 shapeIntersection(class CollisionShapeComponent *shapeComponent);
    virtual void writePacket(OutputStream *out) override;

private:
    Actor *mBulletOwner;
    glm::vec2 mForward;
};

#endif