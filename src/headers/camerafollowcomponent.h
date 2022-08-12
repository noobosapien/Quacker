#ifndef CAMERA_FOLLOW_COMPONENT_H
#define CAMERA_FOLLOW_COMPONENT_H

class CameraFollowComponent : public Component
{
public:
    CameraFollowComponent(Actor *owner);
    ~CameraFollowComponent();

    virtual void update(float delta) override;

private:
};

#endif