#ifndef CUBE_COMPONENT_H
#define CUBE_COMPONENT_H

class CubeComponent : public RenderComponent
{

public:
    CubeComponent(class Actor *owner, class Renderer *renderer, int drawOrder = 100);
    virtual ~CubeComponent();

    virtual void draw() override;
    virtual void setTexture(class Texture *texture);

    int getTexWidth() { return mTexWidth; }
    int getTexHeight() { return mTexHeight; }

private:
    class Texture *mTexture;

    int mTexWidth;
    int mTexHeight;
};

#endif