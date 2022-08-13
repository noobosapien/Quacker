#ifndef PLAYER_H
#define PLAYER_H

class Player : public Actor
{
public:
    Player(Game *game, bool left);
    ~Player();

    friend class Utils;

    void updateActor(float delta) override;

private:
    bool mLeft;
    class MoveComponent *mMovement;
};

#endif