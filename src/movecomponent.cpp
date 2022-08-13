#include "headers/gamepch.h"

MoveComponent::MoveComponent(Actor *owner, CollisionComponent *collider, int updateOrder)
    : Component(owner, updateOrder), mCollider(collider)
{
    mDirection = glm::vec2(0.f);
    mSpeed = 0.f;
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::move(bool left, float speed)
{

    mSpeed = speed;

    if (left)
    {
        mDirection = glm::vec2(-1, 0);
    }
    else
    {
        mDirection = glm::vec2(1, 0);
    }
}

void MoveComponent::stop()
{
    mSpeed = 0.f;
    mDirection = glm::vec2(0.f);
}

void MoveComponent::update(float delta)
{
    // check for collision in the environment
    std::vector<Object *> environment = mOwner->getGame()->getEnvironment();

    for (int i = 0; i < environment.size(); i++)
    {
        glm::vec2 dir = mCollider->intersect(environment[i]->getCollider());

        if (dir.x > 0 || dir.y > 0 || dir.x < 0 || dir.y < 0)
        {
            // mColDirection = dir;
        }
    }

    glm::vec2 pos = mOwner->getPosition();

    pos += mDirection * mSpeed * delta;
    mOwner->setPosition(pos);
}