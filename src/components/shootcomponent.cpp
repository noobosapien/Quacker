#include "../headers/gamepch.h"

ShootComponent::ShootComponent(Actor *owner, bool interpolate) : Component(owner),
                                                                 mCharge(0.f),
                                                                 mStart(false)
{
}

ShootComponent::~ShootComponent()
{
}

void ShootComponent::update(float delta)
{

    if (mStart)
    {
        mCharge += delta;

        if (mCharge >= 3.f)
        {
            shoot();
            mStartTime = mOwner->getGame()->getCurrentTime();
            mCharge = 0.f;
        }
    }
    removeOutBullets();
}

void ShootComponent::startToShoot()
{
    if (!mStart)
    {
        mStartTime = mOwner->getGame()->getCurrentTime();
        mStart = true;
    }
}

void ShootComponent::stopShoot()
{
    mStartTime = 0.;
    mStart = false;
    mCharge = 0.f;
}

void ShootComponent::shoot()
{
    auto bullet = new Bullet(mOwner->getGame(), mOwner, mOwner->getRotation() - 90, mStartTime);

    mNewBullets.push_back(bullet);
    mOwner->getGame()->setBullet(bullet, mOwner);
}

void ShootComponent::shootAtDirection(glm::vec2 pos, float rot, double startTime) // only called from server
{
    auto bullet = new Bullet(mOwner->getGame(), mOwner, pos, rot, startTime);
    mOwner->getGame()->setBullet(bullet, mOwner);
}

void ShootComponent::writePacket(OutputStream *out)
{
    out->write(std::string("3"));                   // bullets
    out->write(std::to_string(mNewBullets.size())); // no of bullets

    for (int i = 0; i < mNewBullets.size(); i++)
    {
        mNewBullets[i]->writePacket(out);
    }

    mNewBullets.clear();
}

void ShootComponent::removeOutBullets()
{

    std::vector<Bullet *> &bullets = mOwner->getGame()->getBullets(mOwner);

    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i]->getPosition().x < -1.f ||
            bullets[i]->getPosition().x > 1.f ||
            bullets[i]->getPosition().y < -1.f ||
            bullets[i]->getPosition().y > 1.f)
        {
            bullets.erase(bullets.begin() + i);
        }
    }
}