#ifndef COLLISION_SHAPE_COMPONENT_H
#define COLLISION_SHAPE_COMPONENT_H

class CollisionShapeComponent : public Component
{
public:
    enum class SHAPE_TYPE
    {
        CIRCLE,
        RECTANGLE
    };

    CollisionShapeComponent(Actor *owner, SHAPE_TYPE type);
    ~CollisionShapeComponent();

    virtual void update(float delta) override;
    virtual glm::vec3 shapeIntersection(CollisionShapeComponent *shapeComponent) = 0;

    SHAPE_TYPE getType() { return mType; }

private:
    SHAPE_TYPE mType;
};

#endif