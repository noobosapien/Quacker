#include "headers/gamepch.h"

AIComponent::AIComponent(Actor *actor, MoveComponent *movecomp, bool left, RotationComponent *rotComp) : Component(actor),
                                                                                                         mState(STATE::GO_DOWN),
                                                                                                         mMoveComp(movecomp),
                                                                                                         mLeft(left),
                                                                                                         mRotComp(rotComp),
                                                                                                         mLastPacketTime(0.0)
{
    setState(STATE::GO_DOWN);
}

AIComponent::~AIComponent()
{
}

void AIComponent::update(float delta)
{

    // createPacket();

    // if (mState == GO_DOWN && mMoveComp->getColDirection().y > 0.f)
    // {
    //     mLeft ? setState(GO_LEFT) : setState(GO_RIGHT);
    // }

    // if ((mState == GO_LEFT || mState == GO_RIGHT) && (mMoveComp->getColDirection().x < 0.f || mMoveComp->getColDirection().x > 0.f))
    // {
    //     setState(GO_UP);
    // }
}

void AIComponent::setState(STATE state)
{
    // switch (state)
    // {
    // case GO_DOWN:
    //     mMoveComp->setDirection(glm::vec2(0.f, -1.f));
    //     mMoveComp->setSpeed(0.4f);
    //     mRotComp->setSpeed(100);
    //     mState = GO_DOWN;
    //     break;

    // case GO_UP:
    //     mMoveComp->setDirection(glm::vec2(0.f, 1.f));
    //     mMoveComp->setSpeed(0.1f);
    //     mRotComp->setSpeed(500);
    //     mState = GO_UP;
    //     break;

    // case GO_LEFT:
    //     mMoveComp->setDirection(glm::vec2(-1.f, 0.f));
    //     mMoveComp->setSpeed(0.2f);
    //     mRotComp->setSpeed(300);
    //     mState = GO_LEFT;
    //     break;

    // case GO_RIGHT:
    //     mMoveComp->setDirection(glm::vec2(1.f, 0.f));
    //     mMoveComp->setSpeed(0.2f);
    //     mRotComp->setSpeed(300);
    //     mState = GO_RIGHT;
    //     break;

    // default:
    //     mMoveComp->setDirection(glm::vec2(0.f, 0.f));
    //     mRotComp->setSpeed(0);
    //     mState = GO_NOWHERE;
    //     break;
    // }
}

void AIComponent::createPacket()
{
    if ((mOwner->getGame()->getCurrentTime() - mLastPacketTime) > 60)
    {
        OutputStream *out = new OutputStream();

        uint32_t stat = 'UPDT';
        out->writeBytes(&stat, 4);
        out->write(std::to_string(mOwner->getGame()->getWebsocket()->getPID()));
        out->write(std::string("1")); // height
        int height = mOwner->getPosition().y * 1000000;

        out->write(std::to_string(height));

        mOwner->getGame()->getWebsocket()->setOutgoing(out);

        mLastPacketTime = mOwner->getGame()->getCurrentTime();
    }
}