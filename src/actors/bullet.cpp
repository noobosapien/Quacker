#include "../headers/gamepch.h"

Bullet::Bullet(Game *game, Actor *owner, float rotation, double startTime) : Actor(game),
                                                                             mBulletOwner(owner),
                                                                             mStartTime(startTime)
{

    setScale(0.01);
    setRotation(rotation);
    setPosition(mBulletOwner->getPosition());

    SpriteComponent *sc = new SpriteComponent(this, getGame()->getRenderer(), 10);
    sc->setTexture(getGame()->getRenderer()->getTexture("src/assets/textures/Bullet1.png"));

    CircleShapeComponent *csc = new CircleShapeComponent(this, static_cast<float>(getScale()));
    CollisionComponent *cc = new CollisionComponent(this, csc);

    new BulletMoveComponent(this, cc, false);
    mShootTime = getGame()->getCurrentTime();
}

Bullet::Bullet(Game *game, Actor *owner, glm::vec2 position, float rotation, double startTime) : Actor(game),
                                                                                                 mBulletOwner(owner),
                                                                                                 mStartTime(startTime)
{
    setScale(0.01);
    setRotation(rotation);
    setPosition(position);

    SpriteComponent *sc = new SpriteComponent(this, getGame()->getRenderer(), 10);
    sc->setTexture(getGame()->getRenderer()->getTexture("src/assets/textures/Bullet1.png"));

    CircleShapeComponent *csc = new CircleShapeComponent(this, static_cast<float>(getScale()));
    CollisionComponent *cc = new CollisionComponent(this, csc);

    new BulletMoveComponent(this, cc, false);
    mShootTime = getGame()->getCurrentTime();
}

Bullet::~Bullet()
{
}

void Bullet::updateActor(float delta)
{
}

void Bullet::writePacket(OutputStream *out)
{
    out->write(std::to_string(mStartTime)); // for load time
    out->write(std::to_string(mShootTime));

    out->write(std::to_string(getPosition().x * 1000000));
    out->write(std::to_string(getPosition().y * 1000000));

    out->write(std::to_string(getRotation() * 1000000));
}

// EMSCRIPTEN_BINDINGS(bullet_smart_pointer)
// {
//     emscripten::class_<Bullet>("Bullet")
//         .constructor<Game *, Actor *, float, double>()
//         .constructor<Game *, Actor *, glm::vec2, float, double>()
//         .smart_ptr<std::shared_ptr<Bullet>>("Bullet");
// }