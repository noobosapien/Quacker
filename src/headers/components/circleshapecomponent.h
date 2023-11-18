#ifndef CIRCLE_SHAPE_COMPONENT_H
#define CIRCLE_SHAPE_COMPONENT_H

class CircleShapeComponent : public CollisionShapeComponent
{
public:
    CircleShapeComponent(Actor *owner, float radius);
    ~CircleShapeComponent();

    virtual void update(float delta) override;
    virtual glm::vec3 shapeIntersection(CollisionShapeComponent *shapeComponent) override;

    inline float getRadius() { return mRadius; }

    inline glm::vec3 getPosition()
    {
        return mOwner->getPosition();
    }

private:
    float mRadius;
};

#endif