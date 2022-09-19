#include "../headers/gamepch.h"

NetworkComponent::NetworkComponent(Actor *owner) : Component(owner), mLastPacketTime(0.)
{
}

NetworkComponent::~NetworkComponent()
{
}

void NetworkComponent::update(float delta)
{
    setPacket();
}

void NetworkComponent::setPacket()
{

    OutputStream *out = new OutputStream();

    uint32_t stat = 'UPDT';
    out->writeBytes(&stat, 4);
    out->write(std::to_string(uint32_t(mOwner->getGame()->getCurrentTime())));
    out->write(std::to_string(mOwner->getGame()->getWebsocket()->getPID()));

    mOwner->writePacket(out);

    mOwner->getGame()->getWebsocket()->setOutgoing(out);

    mLastPacketTime = mOwner->getGame()->getCurrentTime();
}