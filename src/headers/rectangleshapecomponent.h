#ifndef RECTANGLE_SHAPE_COMPONENT_H
#define RECTANGLE_SHAPE_COMPONENT_H

class RectangleShapeComponent : public CollisionShapeComponent
{
public:
    RectangleShapeComponent(Actor *owner, float width, float height);
    ~RectangleShapeComponent();

    virtual void update(float delta) override;
    virtual glm::vec2 shapeIntersection(CollisionShapeComponent *shapeComponent) override;
    glm::vec2 getStart();
    glm::vec2 getSize() { return glm::vec2(mWidth, mHeight); }

private:
    float mWidth;
    float mHeight;
};

#endif