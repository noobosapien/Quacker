#include "../headers/gamepch.h"

int Bullet::mTotalIDs = 1;

Bullet::Bullet(Game *game, Actor *owner, float rotation, double startTime) : Actor(game),
                                                                             mBulletOwner(owner),
                                                                             mStartTime(startTime),
                                                                             mCollider(nullptr),
                                                                             mSprite(nullptr)
{

    mId = Bullet::mTotalIDs++;

    setScale(0.01);
    setRotation(rotation);
    setPosition(mBulletOwner->getPosition());

    mSprite = new SpriteComponent(this, getGame()->getRenderer(), 10);
    mSprite->setTexture(getGame()->getRenderer()->getTexture("src/assets/textures/Bullet1.png"));

    CircleShapeComponent *csc = new CircleShapeComponent(this, static_cast<float>(getScale()));
    mCollider = new CollisionComponent(this, csc);

    new BulletMoveComponent(this, mCollider, false);
    mShootTime = getGame()->getCurrentTime();
}

Bullet::Bullet(Game *game, Actor *owner, glm::vec2 position, float rotation, double startTime) : Actor(game),
                                                                                                 mBulletOwner(owner),
                                                                                                 mStartTime(startTime),
                                                                                                 mCollider(nullptr),
                                                                                                 mSprite(nullptr)
{

    mId = Bullet::mTotalIDs++;
    setScale(0.01);
    setRotation(rotation);
    setPosition(position);

    mSprite = new SpriteComponent(this, getGame()->getRenderer(), 1);
    mSprite->setTexture(getGame()->getRenderer()->getTexture("src/assets/textures/Bullet1.png"));

    CircleShapeComponent *csc = new CircleShapeComponent(this, static_cast<float>(getScale()));
    mCollider = new CollisionComponent(this, csc);

    new BulletMoveComponent(this, mCollider, false);
    mShootTime = getGame()->getCurrentTime();
}

Bullet::~Bullet()
{
}

Bullet &Bullet::operator=(const Bullet &bullet)
{
    mBulletOwner = bullet.mBulletOwner;
    mCollider = bullet.mCollider;
    mGo = bullet.mGo;
    mStartTime = bullet.mStartTime;
    mShootTime = bullet.mShootTime;

    return *this;
}

bool operator==(const Bullet b1, const Bullet b2)
{
    return b1.mId == b2.mId;
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