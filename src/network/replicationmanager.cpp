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