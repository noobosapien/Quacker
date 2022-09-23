#ifndef SHOOT_COMPONENT_H
#define SHOOT_COMPONENT_H

class ShootComponent : public Component
{
public:
    ShootComponent(Actor *owner, bool interpolate);
    ~ShootComponent();

    virtual void update(float delta) override;

    void startToShoot();
    void stopShoot();

    void shootAtDirection(glm::vec2 pos, float rotation, double startTime);

    void writePacket(OutputStream *out);

private:
    bool mStart;
    float mCharge;
    double mStartTime;

    std::vector<Bullet *> mNewBullets;

    void shoot();
    void removeOutBullets();
};

#endif