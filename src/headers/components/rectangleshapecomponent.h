#ifndef RECTANGLE_SHAPE_COMPONENT_H
#define RECTANGLE_SHAPE_COMPONENT_H

class RectangleShapeComponent : public CollisionShapeComponent
{
public:
    RectangleShapeComponent(Actor *owner, float width, float height);
    ~RectangleShapeComponent();

    virtual void update(float delta) override;
    virtual glm::vec3 shapeIntersection(CollisionShapeComponent *shapeComponent) override;
    glm::vec3 getStart();
    glm::vec3 getSize() { return glm::vec3(mWidth, mHeight, 0.f); }

private:
    float mWidth;
    float mHeight;
};

#endif