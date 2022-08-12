#ifndef AICOMP_H
#define AICOMP_H

class AIComponent : public Component
{
public:
    AIComponent(Actor *owner, MoveComponent *movecomp, bool left, RotationComponent *rotComp);
    ~AIComponent();

    void update(float delta) override;

private:
    enum STATE
    {
        GO_RIGHT = 1,
        GO_LEFT,
        GO_UP,
        GO_DOWN,
        GO_NOWHERE
    };

    STATE mState;

    void setState(STATE state);
    void createPacket();

    MoveComponent *mMoveComp;
    RotationComponent *mRotComp;
    bool mLeft;
    double mLastPacketTime;
};

#endif