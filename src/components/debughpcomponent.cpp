#include "../headers/gamepch.h"

DebugHPComponent::DebugHPComponent(Actor *owner, CollisionComponent *collider, bool isEnemy) : Component(owner),
                                                                                               mCollider(collider),
                                                                                               mHealth(100),
                                                                                               mEnemyHealth(100),
                                                                                               mIsEnemy(isEnemy)
{
}

DebugHPComponent::~DebugHPComponent()
{
}

void DebugHPComponent::update(float delta)
{
    if (mIsEnemy)
        return;

    std::vector<Bullet *> &eBullets = mOwner->getGame()->getBullets(mOwner->getGame()->getEnemy());

    for (Bullet *bullet : eBullets)
    {
        glm::vec3 collision = mCollider->intersect(bullet->getCollider());

        if (collision.x > 0)
        {
            auto iter = std::find(eBullets.begin(), eBullets.end(), bullet);
            if (iter != eBullets.end())
            {
                std::iter_swap(iter, eBullets.end() - 1);
                eBullets.pop_back();
            }

            bullet->setState(Actor::EDead);
            mDestroyedBullets.push_back(bullet->getID());

            std::cout << "Id of the deleted: " << bullet->getID() << std::endl;

            updateHp(mHealth - 10);
        }
    }
}

void DebugHPComponent::writePacket(OutputStream *out)
{

    out->write(std::string("4"));
    out->write(std::to_string(mDestroyedBullets.size()));

    for (int i = 0; i < mDestroyedBullets.size(); i++)
    {
        out->write(std::to_string(mDestroyedBullets[i]));
    }

    mDestroyedBullets.clear();

    out->write(std::string("5"));
    out->write(std::to_string(mHealth));
}