#include "../headers/gamepch.h"

Bullet::Bullet(Game *game, Actor *owner, glm::vec2 forward) : Actor(game), mBulletOwner(owner), mForward(forward)
{
    setScale(0.1);

    SpriteComponent *sc = new SpriteComponent(this, 150);
    sc->setTexture(game->getTexture("src/assets/textures/Ship1.png"));

    CircleShapeComponent *csc = new CircleShapeComponent(this, static_cast<float>(getScale()));
    CollisionComponent *cc = new CollisionComponent(this, csc);
}
Bullet::~Bullet()
{
}

void Bullet::updateActor(float delta)
{
}

glm::vec2 Bullet::shapeIntersection(CollisionShapeComponent *shapeComponent)
{
    return glm::vec2(0.f);
}

void Bullet::writePacket(OutputStream *out)
{
}