#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Actor
{
public:
    Enemy(Game *game, bool left);
    ~Enemy();

    void updateActor(float delta) override;
    void interpolateTo(float delta);

    void setInterpolationPosition(glm::vec2 newPos) { mInterpolateTo = newPos; }

private:
    glm::vec2 mInterpolateTo;
    bool mLeft;
};

#endif