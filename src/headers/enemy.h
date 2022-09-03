#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Actor
{
public:
    Enemy(Game *game, bool left);
    ~Enemy();

    void updateActor(float delta) override;
    class MoveComponent *getMoveComponent() { return mMovement; }

private:
    bool mLeft;
    class MoveComponent *mMovement;
};

#endif