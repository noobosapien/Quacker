#include "headers/gamepch.h"

CollisionShapeComponent::CollisionShapeComponent(Actor *owner, SHAPE_TYPE type) : Component(owner), mType(type)
{
}

CollisionShapeComponent::~CollisionShapeComponent()
{
}

void CollisionShapeComponent::update(float delta)
{
}
