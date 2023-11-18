#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H

class CollisionComponent : public Component
{
public:
    CollisionComponent(Actor *owner, class CollisionShapeComponent *shape);
    ~CollisionComponent();

    virtual void update(float delta) override;

    glm::vec3 intersect(CollisionComponent *collider);
    class CollisionShapeComponent *getShape() { return mShape; }

private:
    class CollisionShapeComponent *mShape;
};

#endif