#ifndef CIRCLE_RENDER_COMPONENT_H
#define CIRCLE_RENDER_COMPONENT_H

class CircleRenderComponent : public RenderComponent
{

public:
    CircleRenderComponent(class Actor *owner, Renderer *renderer, int drawOrder);
    virtual ~CircleRenderComponent();

    virtual void draw() override;

    virtual void update(float delta) override;

private:
};

#endif