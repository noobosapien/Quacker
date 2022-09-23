#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

class RenderComponent : public Component
{

public:
    RenderComponent(class Actor *owner, class Renderer *renderer, int drawOrder = 100);
    virtual ~RenderComponent();

    virtual void draw() = 0;

    int getDrawOrder() { return mDrawOrder; }

protected:
    Renderer *mRenderer;
    Shader *mShader;
    int mDrawOrder;
};

#endif