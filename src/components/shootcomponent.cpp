#include "../headers/gamepch.h"

ShootComponent::ShootComponent(Actor *owner) : Component(owner)
{
}

ShootComponent::~ShootComponent()
{
}

void ShootComponent::update(float delta)
{
}

glm::vec2 ShootComponent::shapeIntersection(CollisionShapeComponent *shapeComponent)
{
    return glm::vec2(0.f);
}

void ShootComponent::startToShoot()
{
}

void ShootComponent::stopShoot()
{
}