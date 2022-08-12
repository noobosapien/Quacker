#include "headers/gamepch.h"

CollisionComponent::CollisionComponent(Actor *owner, CollisionShapeComponent *shape) : Component(owner), mShape(shape)
{
}

CollisionComponent::~CollisionComponent()
{
}

void CollisionComponent::update(float delta)
{
}

glm::vec2 CollisionComponent::intersect(CollisionComponent *collider)
{
    return mShape->shapeIntersection(collider->getShape());
}