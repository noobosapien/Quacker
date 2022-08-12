#ifndef CIRCLE_SHAPE_COMPONENT_H
#define CIRCLE_SHAPE_COMPONENT_H

class CircleShapeComponent : public CollisionShapeComponent
{
public:
    CircleShapeComponent(Actor *owner, float radius);
    ~CircleShapeComponent();

    virtual void update(float delta) override;
    virtual glm::vec2 shapeIntersection(CollisionShapeComponent *shapeComponent) override;

    float getRadius() { return mRadius; }

private:
    float mRadius;
};

#endif