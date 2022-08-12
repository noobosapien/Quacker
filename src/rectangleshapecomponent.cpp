#include "headers/gamepch.h"

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

glm::vec2 RectangleShapeComponent::shapeIntersection(CollisionShapeComponent *shapeComponent)
{
    return glm::vec2(0.f);
}

glm::vec2 RectangleShapeComponent::getStart()
{
    return glm::vec2(mOwner->getPosition().x - (mWidth / 2.f), mOwner->getPosition().y - (mHeight / 2.f));
    // return glm::vec2(mOwner->getPosition().x - (mWidth / 1.f), mOwner->getPosition().y - (mHeight / 1.f));
    // return glm::vec2(mOwner->getPosition().x, mOwner->getPosition().y);
}
