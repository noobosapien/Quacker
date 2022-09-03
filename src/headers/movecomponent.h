#ifndef MOVECOMP_H
#define MOVECOMP_H

#define PI 3.14159265359

class MoveComponent : public Component
{
public:
    MoveComponent(Actor *owner, class CollisionComponent *collider, bool interpolate, int updateOrder = 10);
    ~MoveComponent();

    void update(float delta) override;

    void move(bool left, float speed);
    void stop();

    void rotate(bool left, float speed);
    void stopRotate();

    void setToPosition(glm::vec2 position) { mToPosition = position; }
    void setToRotation(float rotation) { mToRotation = rotation; }

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

    template <typename T>
    T linearInterpolate(T value, T to, float time);

    void interpolatePosition(float delta);
    void interpolateRotation(float delta);
};

#endif