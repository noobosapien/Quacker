#ifndef PLAYER_H
#define PLAYER_H

class Player : public Actor
{
public:
    Player(Game *game, bool left);
    ~Player();

    void updateActor(float delta) override;

private:
    bool mLeft;
};

#endif