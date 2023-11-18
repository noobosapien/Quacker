#include "../headers/gamepch.h"

ReplicationManager::ReplicationManager(Game *game)
{
    mGame = game;
}

void ReplicationManager::read(InputStream &inStream)
{

    while (inStream.getRemainingBitCount() > 8)
    {

        uint32_t action; // doesn't have to be 32bits
        inStream.read(action);

        if (Game::DEBUG)
            printf("ReplicationManager::read Replication manager read Here action: %u\n", action);

        switch (action)
        {
        case RA_ENEMY_POS:
            updateEnemyPos(inStream);
            break;

        case RA_ENEMY_ROT:
            updateEnemyRot(inStream);
            break;

        case RA_ENEMY_BULLETS:
            addEnemyBullets(inStream);
            break;

        case RA_REMOVE_BULLETS:
            removeBullets(inStream);
            break;

        case RA_ENEMY_HEALTH:
            updateEnemyHealth(inStream);
            break;

        default:
            break;
        }
    }
}

void ReplicationManager::updateEnemyPos(InputStream &inStream)
{
    int32_t enemyPos(0);

    inStream.read(enemyPos);

    // std::cout << "Enemy position: " << enemyPos << std::endl;
    // movement component interpolate position to the new position
    mGame->getEnemy()->getMoveComponent()->setToPosition(glm::vec3(float(enemyPos) / -1000000, mGame->getEnemy()->getPosition().y, 0.0));
}

void ReplicationManager::updateEnemyRot(InputStream &inStream)
{
    int32_t enemyRot(0);

    inStream.read(enemyRot);

    mGame->getEnemy()->getMoveComponent()->setToRotation((float(enemyRot) / 1000000) - 180.f);
}

void ReplicationManager::addEnemyBullets(InputStream &inStream)
{
    int32_t noOfBullets(0);
    inStream.read(noOfBullets);

    for (int i = 0; i < noOfBullets; i++)
    {
        int32_t posX; // posX
        int32_t posY; // posY
        int32_t rot;  // rot

        inStream.read(posX);
        inStream.read(posY);
        inStream.read(rot);

        auto enemy = mGame->getEnemy();

        // change the type shoot at direction is immediate
        enemy->getShootComponent()->shootAtDirection(Bullet::Type::BULLET, glm::vec3(float(posX) / -1000000, enemy->getPosition().y, 0.0),
                                                     (float(rot) / 1000000) - 180.f,
                                                     mGame->getCurrentTime());
    }
}

void ReplicationManager::removeBullets(InputStream &inputStream)
{
    int32_t noOfBullets;
    int32_t bulletId;

    inputStream.read(noOfBullets);
    if (noOfBullets > 0)
    {

        std::vector<Bullet *> &eBullets = mGame->getBullets(mGame->getPlayer());
        std::vector<int> bulletIDs;

        for (int32_t i = 0; i < noOfBullets; i++)
        {
            inputStream.read(bulletId);
            bulletIDs.push_back(static_cast<int>(bulletId));
        }

        for (int id : bulletIDs)
        {
            for (Bullet *bullet : eBullets)
            {
                if (bullet->getID() == id)
                {
                    auto iter = std::find(eBullets.begin(), eBullets.end(), bullet);
                    if (iter != eBullets.end())
                    {
                        std::iter_swap(iter, eBullets.end() - 1);
                        eBullets.pop_back();
                    }

                    bullet->setState(Actor::EDead);
                }
            }
        }
    }
}

void ReplicationManager::updateEnemyHealth(InputStream &inputStream)
{
    int32_t health(0);
    inputStream.read(health);

    if (health <= 100 && health >= 0)
    {
        mGame->getEnemy()->getHpComponent()->updateHp(static_cast<int>(health));
    }
}