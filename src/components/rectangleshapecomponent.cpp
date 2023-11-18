#include "../headers/gamepch.h"

RectangleShapeComponent::RectangleShapeComponent(Actor *owner, float width, float height) : CollisionShapeComponent(owner, CollisionShapeComponent::SHAPE_TYPE::RECTANGLE),
                                                                                            mWidth(width), mHeight(height)
{
}

RectangleShapeComponent::~RectangleShapeComponent()
{
}

void RectangleShapeComponent::update(float delta)
{
}

glm::vec3 RectangleShapeComponent::shapeIntersection(CollisionShapeComponent *shapeComponent)
{
    return glm::vec3(0.f);
}

glm::vec3 RectangleShapeComponent::getStart()
{
    return glm::vec3(mOwner->getPosition().x - (mWidth / 2.f), mOwner->getPosition().y - (mHeight / 2.f), 0.f);
}
