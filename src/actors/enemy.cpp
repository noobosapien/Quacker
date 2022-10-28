#include "../headers/gamepch.h"

Enemy::Enemy(Game *game) : Actor(game), mMovement(nullptr), mCharge(nullptr), mHp(nullptr)
{
    setScale(0.11);

    SpriteComponent *sc = new SpriteComponent(this, getGame()->getRenderer(), 150);
    sc->setTexture(getGame()->getRenderer()->getTexture("src/assets/textures/Ship2.png"));

    CircleShapeComponent *csc = new CircleShapeComponent(this, static_cast<float>(getScale()));
    CollisionComponent *cc = new CollisionComponent(this, csc);

    glm::vec2 dir;

    setPosition(glm::vec2(0.f, 0.4f));

    mMovement = new MoveComponent(this, cc, true);
    mCharge = new ChargingComponent(this, getGame()->getRenderer(), 140);
    mShoot = new ShootComponent(this, true, mCharge);
    mHp = new DebugHPComponent(this, cc, true);
    // new AIComponent(this, mc, left, rot);
}

Enemy::~Enemy()
{
}

void Enemy::updateActor(float delta)
{
    Actor::updateActor(delta);
}
