#ifndef MOVECOMP_H
#define MOVECOMP_H

#define PI 3.14159265359

class AIComponent;

class MoveComponent : public Component
{
public:
    friend class AIComponent;

    MoveComponent(Actor *owner, class CollisionComponent *collider, glm::vec2 dir, int updateOrder = 10);
    ~MoveComponent();

    void update(float delta) override;

private:
    class CollisionComponent *mCollider;
    glm::vec2 mDirection;
    glm::vec2 mColDirection;
    glm::vec2 mOriginalDir;
    float mSpeed;

    glm::vec2 getColDirection() { return mColDirection; }
    glm::vec2 getOriginalDirection() { return mOriginalDir; }

    void setSpeed(float speed) { mSpeed = speed; }
    void setDirection(glm::vec2 direction) { mDirection = direction; }
};

#endif