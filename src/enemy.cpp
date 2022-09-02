#include "headers/gamepch.h"

Enemy::Enemy(Game *game, bool left) : Actor(game), mLeft(left), mInterpolateTo(glm::vec2(0.f))
{
    setScale(0.1);
    if (mLeft)
    {
        // setPosition(glm::vec2(-80.f / Game::WIN_WIDTH, -700.f / Game::WIN_HEIGHT));
        // setPosition(glm::vec2(-80.f / Game::WIN_WIDTH, -0.4f));
    }
    else
    {
        // setPosition(glm::vec2(80.f / Game::WIN_WIDTH, -700.f / Game::WIN_HEIGHT));
        // setPosition(glm::vec2(80.f / Game::WIN_WIDTH, -0.4f));
    }

    SpriteComponent *sc = new SpriteComponent(this, 150);
    sc->setTexture(game->getTexture("src/assets/textures/enemy.png"));

    CircleShapeComponent *csc = new CircleShapeComponent(this, static_cast<float>(getScale()));
    CollisionComponent *cc = new CollisionComponent(this, csc);

    glm::vec2 dir;

    RotationComponent *rot = nullptr;

    if (mLeft)
    {
        // dir = glm::vec2(-1, 1);
        // rot = new RotationComponent(this, true, 300);
    }
    else
    {
        // dir = glm::vec2(1, 1);
        // rot = new RotationComponent(this, false, 300);
    }
    setPosition(glm::vec2(0.f, 0.4f));

    // MoveComponent *mc = new MoveComponent(this, cc, dir);
    // new AIComponent(this, mc, left, rot);
}

Enemy::~Enemy()
{
}

void Enemy::updateActor(float delta)
{
    Actor::updateActor(delta);
    interpolateTo(delta);
}

void Enemy::interpolateTo(float delta)
{
    this->interpolatePosition(mInterpolateTo, delta);
}