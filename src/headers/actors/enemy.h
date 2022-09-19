#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Actor
{
public:
    Enemy(Game *game);
    ~Enemy();

    void updateActor(float delta) override;
    class MoveComponent *getMoveComponent() { return mMovement; }

private:
    class MoveComponent *mMovement;
};

#endif