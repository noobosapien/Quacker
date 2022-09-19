#ifndef SHOOT_COMPONENT_H
#define SHOOT_COMPONENT_H

class ShootComponent : public Component
{
public:
    ShootComponent(Actor *owner);
    ~ShootComponent();

    virtual void update(float delta) override;

    void startToShoot();
    void stopShoot();

private:
    float mWidth;
    float mHeight;
};

#endif