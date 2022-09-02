#ifndef PLAYER_H
#define PLAYER_H

class Player : public Actor
{
public:
    Player(Game *game, bool left);
    ~Player();

    friend class Utils;

    void updateActor(float delta) override;
    void interpolateTo(float delta);

    void setInterpolationPosition(glm::vec2 newPos) { mInterpolateTo = newPos; }

private:
    bool mLeft;
    glm::vec2 mInterpolateTo;
    class MoveComponent *mMovement;
};

#endif