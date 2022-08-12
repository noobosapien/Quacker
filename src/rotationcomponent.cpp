#include "headers/gamepch.h"

RotationComponent::RotationComponent(Actor *owner, bool clockwise, unsigned int speed) : Component(owner),
                                                                                         mClockwise(clockwise), mSpeed(speed)
{
}

RotationComponent::~RotationComponent()
{
}

void RotationComponent::update(float delta)
{
    if (mClockwise)
    {
        mOwner->setRotation(mOwner->getRotation() + (mSpeed * delta));
    }
    else
    {
        mOwner->setRotation(mOwner->getRotation() - (mSpeed * delta));
    }
}