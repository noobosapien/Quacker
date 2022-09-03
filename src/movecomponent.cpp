#include "headers/gamepch.h"

MoveComponent::MoveComponent(Actor *owner, CollisionComponent *collider, bool interpolate, int updateOrder)
    : Component(owner, updateOrder), mCollider(collider), mInterpolate(interpolate), mPosInterpolateTime(0.f), mRotInterpolateTime(0.f)
{
    mDirection = glm::vec2(0.f);
    mSpeed = 0.f;

    mRotDirection = glm::vec2(0.f);
    mRotSpeed = 0.f;

    mToPosition = mOwner->getPosition();
    mToRotation = mOwner->getRotation();
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

void MoveComponent::rotate(bool left, float speed)
{
    mRotSpeed = speed;

    if (left)
    {
        mRotDirection = glm::vec2(-1, 0);
    }
    else
    {
        mRotDirection = glm::vec2(1, 0);
    }
}

void MoveComponent::stopRotate()
{
    mRotSpeed = 0.f;
    mRotDirection = glm::vec2(0.f);
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

    if (mInterpolate)
    {
        interpolatePosition(delta);
        interpolateRotation(delta);
    }
    else
    {
        if (pos.x < 0.5 && mDirection.x > 0)
        {
            pos += mDirection * mSpeed * delta;
            mOwner->setPosition(pos);
        }
        else if (pos.x > -0.5 && mDirection.x < 0)
        {
            pos += mDirection * mSpeed * delta;
            mOwner->setPosition(pos);
        }

        float rot = mOwner->getRotation();

        if (mRotDirection.x < 0 && rot < 270)
        {
            mOwner->setRotation(rot + (mRotSpeed * delta));
        }
        else if (mRotDirection.x > 0 && rot > 90)
        {
            mOwner->setRotation(rot - (mRotSpeed * delta));
        }
    }
}

template <typename T>
T MoveComponent::linearInterpolate(T value, T to, float time)
{
    return value + (to - value) * time;
}

void MoveComponent::interpolatePosition(float delta)
{
    mPosInterpolateTime += 0.1 * delta;

    glm::vec2 position = mOwner->getPosition();

    if (position != mToPosition)
    {
        mOwner->setPosition(linearInterpolate(position, mToPosition, mPosInterpolateTime));
    }

    if (mPosInterpolateTime >= 1.0)
    {
        mPosInterpolateTime = 0.f;
    }
}

void MoveComponent::interpolateRotation(float delta)
{
    mRotInterpolateTime += 0.1 * delta;

    float rotation = mOwner->getRotation();

    if (rotation != mToRotation)
    {
        mOwner->setRotation(linearInterpolate(rotation, mToRotation, mRotInterpolateTime));
    }

    if (mRotInterpolateTime >= 1.0)
    {
        mRotInterpolateTime = 0.f;
    }
}