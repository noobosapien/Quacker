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

        printf("ReplicationManager::read Replication manager read Here action: %u\n", action);

        switch (action)
        {
        case RA_ENEMY_POS:
            updateEnemyPos(inStream);
            break;
        default:
            break;
        }
    }
}

void ReplicationManager::updateEnemyPos(InputStream &inStream)
{
    int32_t enemyPos(0);

    while (inStream.getRemainingBitCount() > 8)
    {
        inStream.read(enemyPos);

        std::cout << "Enemy position: " << enemyPos << std::endl;

        mGame->getEnemy()->setInterpolationPosition(glm::vec2(float(enemyPos) / -1000000, mGame->getEnemy()->getPosition().y));
    }
}