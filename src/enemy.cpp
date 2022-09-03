#include "headers/gamepch.h"

Enemy::Enemy(Game *game, bool left) : Actor(game), mLeft(left)
{
    setScale(0.1);

    SpriteComponent *sc = new SpriteComponent(this, 150);
    sc->setTexture(game->getTexture("src/assets/textures/enemy.png"));

    CircleShapeComponent *csc = new CircleShapeComponent(this, static_cast<float>(getScale()));
    CollisionComponent *cc = new CollisionComponent(this, csc);

    glm::vec2 dir;

    RotationComponent *rot = nullptr;

    setPosition(glm::vec2(0.f, 0.4f));

    mMovement = new MoveComponent(this, cc, true);
    // new AIComponent(this, mc, left, rot);
}

Enemy::~Enemy()
{
}

void Enemy::updateActor(float delta)
{
    Actor::updateActor(delta);
}
