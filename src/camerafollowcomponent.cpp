#include "headers/gamepch.h"

CameraFollowComponent::CameraFollowComponent(Actor *owner) : Component(owner)
{
}

CameraFollowComponent::~CameraFollowComponent()
{
}

void CameraFollowComponent::update(float delta)
{
    if (mOwner->getPosition().y > 0.)
    {
        mOwner->getGame()->getCamera()->setPosition(glm::vec3(0.f, mOwner->getPosition().y, 0.f));
    }
}