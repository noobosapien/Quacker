#ifndef REPLICATIONMANAGER_H
#define REPLICATIONMANAGER_H

class Food;

class ReplicationManager
{

public:
    enum ReplicationAction
    {
        RA_ENEMY_POS
    };

    ReplicationManager() = default;
    ~ReplicationManager() = default;

    ReplicationManager(class Game *game);

    void read(InputStream &inStream);

private:
    void updateEnemyPos(InputStream &inputStream);

    class Game *mGame;
};

#endif