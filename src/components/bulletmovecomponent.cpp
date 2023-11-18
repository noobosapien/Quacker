#include "../headers/gamepch.h"

BulletMoveComponent::BulletMoveComponent(Actor *owner, CollisionComponent *collider, bool interpolate, int updateOrder)
    : Component(owner, updateOrder),
      mCollider(collider),
      mInterpolate(interpolate),
      mPosInterpolateTime(0.f),
      mRotInterpolateTime(0.f),
      mAccelerate(6.f)
{
    mDirection = mOwner->getForward();
    mSpeed = .1f;

    mRotDirection = glm::vec3(0.f);
    mRotSpeed = 0.f;

    mToPosition = mOwner->getPosition();
    mToRotation = mOwner->getRotation();
}

BulletMoveComponent::~BulletMoveComponent()
{
}

void BulletMoveComponent::move(bool left, float speed)
{
    mSpeed = speed;
}

void BulletMoveComponent::stop()
{
    mSpeed = 0.f;
}

void BulletMoveComponent::rotate(bool left, float speed)
{
}

void BulletMoveComponent::stopRotate()
{
    mRotSpeed = 0.f;
    mRotDirection = glm::vec3(0.f);
}

void BulletMoveComponent::update(float delta)
{

    glm::vec3 pos = mOwner->getPosition();

    if (mInterpolate)
    {
        interpolatePosition(delta);
        interpolateRotation(delta);
    }
    else
    {
        if (mAccelerate > 1.f)
        {
            mAccelerate -= 3 * delta;
            pos += mDirection * mSpeed * delta * mAccelerate;
        }
        else
        {
            pos += mDirection * mSpeed * delta;
        }
        mOwner->setPosition(pos);

        // float rot = mOwner->getRotation();

        // if (mRotDirection.x < 0 && rot < 270)
        // {
        //     mOwner->setRotation(rot + (mRotSpeed * delta));
        // }
        // else if (mRotDirection.x > 0 && rot > 90)
        // {
        //     mOwner->setRotation(rot - (mRotSpeed * delta));
        // }
    }
}

void BulletMoveComponent::writePacket(OutputStream *out)
{
    // out->write(std::string("1")); // x direction
    // int height = mOwner->getPosition().x * 1000000;
    // out->write(std::to_string(height));

    // out->write(std::string("2")); // rotation
    // int rotation = mOwner->getRotation() * 1000000;
    // out->write(std::to_string(rotation));
}

template <typename T>
T BulletMoveComponent::linearInterpolate(T value, T to, float time)
{
    return value + (to - value) * time;
}

void BulletMoveComponent::interpolatePosition(float delta)
{
    mPosInterpolateTime += 0.1 * delta;

    glm::vec3 position = mOwner->getPosition();

    if (position != mToPosition)
    {
        mOwner->setPosition(linearInterpolate(position, mToPosition, mPosInterpolateTime));
    }

    if (mPosInterpolateTime >= 1.0)
    {
        mPosInterpolateTime = 0.f;
    }
}

void BulletMoveComponent::interpolateRotation(float delta)
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