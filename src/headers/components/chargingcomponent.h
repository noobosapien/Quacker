#ifndef CHARGING_COMPONENT_H
#define CHARGING_COMPONENT_H

class ChargingComponent : public Component
{

public:
    ChargingComponent(class Actor *owner);
    virtual ~ChargingComponent();

    virtual void draw(class Shader *shader);

    virtual void update(float delta) override;

private:
};

#endif