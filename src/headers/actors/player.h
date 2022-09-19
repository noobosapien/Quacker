#ifndef PLAYER_H
#define PLAYER_H

class Player : public Actor
{
public:
    Player(Game *game);
    ~Player();

    friend class Utils;

    void updateActor(float delta) override;

    class MoveComponent *getMoveComponent() { return mMovement; }

    virtual void writePacket(OutputStream *out) override;

private:
    class MoveComponent *mMovement;
};

#endif