#ifndef REPLICATIONMANAGER_H
#define REPLICATIONMANAGER_H

class Food;

class ReplicationManager
{

public:
    enum ReplicationAction
    {
        RA_ENEMY_POS,
        RA_ENEMY_ROT,
        RA_ENEMY_BULLETS,
        RA_REMOVE_BULLETS,
        RA_ENEMY_HEALTH
    };

    ReplicationManager() = default;
    ~ReplicationManager() = default;

    ReplicationManager(class Game *game);

    void read(InputStream &inStream);

private:
    void updateEnemyPos(InputStream &inputStream);
    void updateEnemyRot(InputStream &inputStream);
    void addEnemyBullets(InputStream &inputStream);
    void removeBullets(InputStream &inputStream);
    void updateEnemyHealth(InputStream &inputStream);

    class Game *mGame;
};

#endif