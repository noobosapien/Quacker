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
    out->write(std::to_string(mOwner->getGame()->getWebsocket()->getPID()));

    out->write(std::string("1")); // x direction
    int height = mOwner->getPosition().x * 1000000;
    out->write(std::to_string(height));

    out->write(std::string("2")); // rotation
    int rotation = mOwner->getRotation() * 1000000;
    out->write(std::to_string(rotation));

    mOwner->getGame()->getWebsocket()->setOutgoing(out);

    mLastPacketTime = mOwner->getGame()->getCurrentTime();
}