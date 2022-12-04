#ifndef LIGHTNING_COMPONENT_H
#define LIGHTNING_COMPONENT_H

class LightningComponent : public RenderComponent
{

public:
    LightningComponent(class Actor *owner, class Renderer *renderer, int drawOrder = 100);
    virtual ~LightningComponent();

    virtual void draw() override;
    virtual void update(float delta) override;

    int getTexWidth() { return mTexWidth; }
    int getTexHeight() { return mTexHeight; }
    float getTime() { return mTime; }

private:
    int mTexWidth;
    int mTexHeight;
    float mTime;
};

#endif