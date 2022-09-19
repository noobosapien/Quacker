#include "../headers/gamepch.h"

CircleShapeComponent::CircleShapeComponent(Actor *owner, float radius) : CollisionShapeComponent(owner, CollisionShapeComponent::SHAPE_TYPE::CIRCLE),
                                                                         mRadius(radius)
{
}

CircleShapeComponent::~CircleShapeComponent()
{
}

void CircleShapeComponent::update(float delta)
{
}

glm::vec2 CircleShapeComponent::shapeIntersection(CollisionShapeComponent *shapeComponent)
{
    switch (shapeComponent->getType())
    {
    case SHAPE_TYPE::CIRCLE:
        // circle circle collision
        return glm::vec2(0.f);
        break;

    case SHAPE_TYPE::RECTANGLE:
        // circle rectangle collision
        RectangleShapeComponent *rect = dynamic_cast<RectangleShapeComponent *>(shapeComponent);

        if (!rect)
            return glm::vec2(0.f);

        float ownerStartX = mOwner->getPosition().x; // - (mOwner->getScale() / 2.f);
        float ownerStartY = mOwner->getPosition().y; // - (mOwner->getScale() / 2.f);

        float testX = ownerStartX;
        float testY = ownerStartY;

        if (ownerStartX < rect->getStart().x)
        {
            testX = rect->getStart().x;
        }
        else if (ownerStartX > rect->getStart().x + rect->getSize().x)
        {
            testX = rect->getStart().x + rect->getSize().x;
        }

        if (ownerStartY < rect->getStart().y)
        {
            testY = rect->getStart().y;
        }
        else if (ownerStartY > rect->getStart().y + rect->getSize().y)
        {
            testY = rect->getStart().y + rect->getSize().y;
        }

        float distX = ownerStartX - testX;
        float distY = ownerStartY - testY;

        float distanceSQ = (distX * distX) + (distY * distY);

        if (distanceSQ < (mRadius) * (mRadius))
        {

            // get the unit vector and invert it
            // return glm::vec2(1.f);
            glm::vec2 norm = glm::normalize(glm::vec2(distX, distY));
            // std::cout << norm.x << ", " << norm.y << std::endl;

            return norm;
        }

        break;
    }

    return glm::vec2(0.f);
}
