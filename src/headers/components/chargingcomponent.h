#ifndef CHARGING_COMPONENT_H
#define CHARGING_COMPONENT_H

class ChargingComponent : public RenderComponent
{

public:
    ChargingComponent(class Actor *owner, Renderer *renderer, int drawOrder);
    virtual ~ChargingComponent();

    virtual void draw() override;

    virtual void update(float delta) override;
    inline void setShow(bool show)
    {
        mShow = show;
    }
    inline void setIntensity(float intensity) { mIntensity = intensity; }

private:
    bool mShow;
    float mIntensity;
};

#endif