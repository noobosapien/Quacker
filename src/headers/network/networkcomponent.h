#ifndef NETWORKCOMP_H
#define NETWORKCOMP_H

class NetworkComponent : public Component
{
public:
    friend class AIComponent;

    NetworkComponent(Actor *owner);
    ~NetworkComponent();

    void update(float delta) override;

private:
    void setPacket(OutputStream *out);
};

#endif