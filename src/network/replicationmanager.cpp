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
    mGame->getEnemy()->getMoveComponent()->setToPosition(glm::vec2(float(enemyPos) / -1000000, mGame->getEnemy()->getPosition().y));
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

        std::cout << float(posX) / 1000000 << ", " << float(posY) / 1000000 << ", " << float(rot) / 1000000 << std::endl;
        auto enemy = mGame->getEnemy();
        enemy->getShootComponent()->shootAtDirection(glm::vec2(float(posX) / -1000000,
                                                               enemy->getPosition().y),
                                                     (float(rot) / 1000000) - 180.f,
                                                     mGame->getCurrentTime());
    }
}