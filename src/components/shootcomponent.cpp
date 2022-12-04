#include "../headers/gamepch.h"

ShootComponent::ShootComponent(Actor *owner, bool interpolate, ChargingComponent *charger) : Component(owner),
                                                                                             mCharge(0.f),
                                                                                             mStart(false),
                                                                                             mCharger(charger),
                                                                                             mGun(1)
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

        mCharger->setIntensity(mCharge);
    }
    removeOutBullets();
}

void ShootComponent::startToShoot()
{
    if (!mStart)
    {
        mStartTime = mOwner->getGame()->getCurrentTime();
        mStart = true;
        mCharger->setShow(true);
    }
}

void ShootComponent::stopShoot()
{
    mStartTime = 0.;
    mStart = false;
    mCharge = 0.f;
    mCharger->setShow(false);
}

void ShootComponent::shoot()
{

    Bullet::Type type;

    switch (mGun)
    {
    case 1:
        type = Bullet::Type::BULLET;
        break;

    case 2:
        type = Bullet::Type::LIGHTNING;
        break;

    default:
        type = Bullet::Type::BULLET;
        break;
    }

    auto bullet = new Bullet(mOwner->getGame(), mOwner, type, mOwner->getRotation() - 90, mStartTime);

    mNewBullets.push_back(bullet);
    mOwner->getGame()->setBullet(bullet, mOwner);
}

void ShootComponent::shootAtDirection(Bullet::Type type, glm::vec2 pos, float rot, double startTime) // only called from server
{
    auto bullet = new Bullet(mOwner->getGame(), mOwner, type, pos, rot, startTime);
    std::cout << "Called shoot at direction" << std::endl;
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
    // std::cout << bullets.size() << std::endl;

    for (int i = 0; i < bullets.size(); i++)
    {
        switch (bullets[i]->getType())
        {
        case Bullet::Type::BULLET:
        {
            if (bullets[i]->getPosition().x < -1.f ||
                bullets[i]->getPosition().x > 1.f ||
                bullets[i]->getPosition().y < -1.f ||
                bullets[i]->getPosition().y > 1.f)
            {
                bullets[i]->setState(Actor::EDead);

                auto iter = std::find(bullets.begin(), bullets.end(), bullets[i]);
                if (iter != bullets.end())
                {
                    std::iter_swap(iter, bullets.end() - 1);
                    bullets.pop_back();
                }
            }

            break;
        }

        case Bullet::Type::LIGHTNING:
        {
            float time = bullets[i]->getLightning()->getTime();

            if (time > 3.f)
            {
                bullets[i]->setState(Actor::EDead);

                auto iter = std::find(bullets.begin(), bullets.end(), bullets[i]);
                if (iter != bullets.end())
                {
                    std::iter_swap(iter, bullets.end() - 1);
                    bullets.pop_back();
                }
            }
            break;
        }

        default:
        {
            break;
        }
        }
    }
}

void ShootComponent::setGun(unsigned int gun)
{
    mGun = gun;

    EM_ASM({UI_RPC("PLAYER_GUN_CHANGE", $0)}, mGun);
}