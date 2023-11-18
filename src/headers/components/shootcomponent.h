#ifndef SHOOT_COMPONENT_H
#define SHOOT_COMPONENT_H

class ShootComponent : public Component
{
public:
    ShootComponent(Actor *owner, bool interpolate, ChargingComponent *charger);
    ~ShootComponent();

    virtual void update(float delta) override;

    void startToShoot();
    void stopShoot();

    void shootAtDirection(Bullet::Type type, glm::vec3 pos, float rotation, double startTime);
    void setGun(unsigned int gun);

    void writePacket(OutputStream *out);

private:
    bool mStart;
    float mCharge;
    double mStartTime;
    unsigned int mGun;
    ChargingComponent *mCharger;

    std::vector<Bullet *> mNewBullets;

    void shoot();
    void removeOutBullets();
};

#endif