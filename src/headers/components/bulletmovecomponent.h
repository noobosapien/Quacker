#ifndef BULLET_MOVECOMP_H
#define BULLET_MOVECOMP_H

#define PI 3.14159265359

class BulletMoveComponent : public Component
{
public:
    BulletMoveComponent(Actor *owner, class CollisionComponent *collider, bool interpolate, int updateOrder = 10);
    ~BulletMoveComponent();

    void update(float delta) override;

    void move(bool left, float speed);
    void stop();

    void rotate(bool left, float speed);
    void stopRotate();

    void setToPosition(glm::vec2 position) { mToPosition = position; }
    void setToRotation(float rotation) { mToRotation = rotation; }

    void writePacket(OutputStream *out);

private:
    class CollisionComponent *mCollider;
    glm::vec2 mDirection;
    float mSpeed;
    glm::vec2 mRotDirection;
    float mRotSpeed;

    glm::vec2 mToPosition;
    float mToRotation;

    bool mInterpolate;
    float mPosInterpolateTime;
    float mRotInterpolateTime;
    float mAccelerate;

    template <typename T>
    T linearInterpolate(T value, T to, float time);

    void interpolatePosition(float delta);
    void interpolateRotation(float delta);
};

#endif