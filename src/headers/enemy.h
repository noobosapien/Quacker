#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Actor
{
public:
    Enemy(Game *game, bool left);
    ~Enemy();

    void updateActor(float delta) override;

private:
    bool mLeft;
};

#endif