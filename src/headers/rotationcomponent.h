#ifndef ROTATION_COMPONENT_H
#define ROTATION_COMPONENT_H

class RotationComponent : public Component
{
public:
    RotationComponent(Actor *owner, bool clockwise, unsigned int speed);
    ~RotationComponent();

    virtual void update(float delta) override;

private:
    bool mClockwise;
    unsigned int mSpeed;

    void setSpeed(unsigned int speed) { mSpeed = speed; }
};

#endif