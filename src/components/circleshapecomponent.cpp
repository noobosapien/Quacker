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

glm::vec3 CircleShapeComponent::shapeIntersection(CollisionShapeComponent *shapeComponent)
{
    switch (shapeComponent->getType())
    {
    case SHAPE_TYPE::CIRCLE:
    {
        // circle circle collision
        CircleShapeComponent *circle = nullptr;
        circle = dynamic_cast<CircleShapeComponent *>(shapeComponent);

        if (circle == nullptr)
        {
            return glm::vec3(0.f);
        }

        float distX = mOwner->getPosition().x - circle->getPosition().x;
        float distY = mOwner->getPosition().y - circle->getPosition().y;

        float distanceSQ = (distX * distX) + (distY * distY);
        // std::cout << distanceSQ << "    " << (this->getRadius() + circle->getRadius()) * (this->getRadius() + circle->getRadius()) << std::endl;
        // std::cout << distanceSQ << "    " << circle->getPosition().y << std::endl;

        if (distanceSQ <= ((this->getRadius() + circle->getRadius()) * (this->getRadius() + circle->getRadius())))
        {
            return glm::vec3(1.f);
        }

        return glm::vec3(0.f);
        break;
    }

    case SHAPE_TYPE::RECTANGLE:
    {
        // circle rectangle collision
        RectangleShapeComponent *rect = static_cast<RectangleShapeComponent *>(shapeComponent);

        if (!rect)
            return glm::vec3(0.f);

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
            glm::vec3 norm = glm::normalize(glm::vec3(distX, distY, 0.f));
            // std::cout << norm.x << ", " << norm.y << std::endl;

            return norm;
        }

        return glm::vec3(0.f);

        break;
    }

    default:
        return glm::vec3(0.f);
    }
}
