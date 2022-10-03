#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Actor
{
public:
    Enemy(Game *game);
    ~Enemy();

    void updateActor(float delta) override;

    class MoveComponent *getMoveComponent() { return mMovement; }
    class ShootComponent *getShootComponent() { return mShoot; }

private:
    class MoveComponent *mMovement;
    class ShootComponent *mShoot;
    class ChargingComponent *mCharge;
};

#endif