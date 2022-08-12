#include "../headers/gamepch.h"

NetworkComponent::NetworkComponent(Actor *owner) : Component(owner)
{
}

NetworkComponent::~NetworkComponent()
{
}

void NetworkComponent::update(float delta)
{
}

void NetworkComponent::setPacket(OutputStream *out)
{
    mOwner->getGame()->getWebsocket()->setOutgoing(out);
}