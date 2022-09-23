#include "../headers/gamepch.h"

Enemy::Enemy(Game *game) : Actor(game)
{
    setScale(0.1);

    SpriteComponent *sc = new SpriteComponent(this, getGame()->getRenderer(), 150);
    sc->setTexture(getGame()->getRenderer()->getTexture("src/assets/textures/Ship2.png"));

    CircleShapeComponent *csc = new CircleShapeComponent(this, static_cast<float>(getScale()));
    CollisionComponent *cc = new CollisionComponent(this, csc);

    glm::vec2 dir;

    setPosition(glm::vec2(0.f, 0.4f));

    mMovement = new MoveComponent(this, cc, true);
    mShoot = new ShootComponent(this, true);
    // new AIComponent(this, mc, left, rot);
}

Enemy::~Enemy()
{
}

void Enemy::updateActor(float delta)
{
    Actor::updateActor(delta);
}
