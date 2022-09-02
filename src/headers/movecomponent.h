#ifndef MOVECOMP_H
#define MOVECOMP_H

#define PI 3.14159265359

class MoveComponent : public Component
{
public:
    MoveComponent(Actor *owner, class CollisionComponent *collider, int updateOrder = 10);
    ~MoveComponent();

    void update(float delta) override;

    void move(bool left, float speed);
    void stop();

    void rotate(bool left, float speed);
    void stopRotate();

private:
    class CollisionComponent *mCollider;
    glm::vec2 mDirection;
    float mSpeed;
    glm::vec2 mRotDirection;
    float mRotSpeed;
};

#endif