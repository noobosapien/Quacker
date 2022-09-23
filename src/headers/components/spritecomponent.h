#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

class SpriteComponent : public RenderComponent
{

public:
    SpriteComponent(class Actor *owner, class Renderer *renderer, int drawOrder = 100);
    virtual ~SpriteComponent();

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