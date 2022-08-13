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

private:
    class CollisionComponent *mCollider;
    glm::vec2 mDirection;
    float mSpeed;
};

#endif