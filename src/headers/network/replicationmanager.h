#ifndef REPLICATIONMANAGER_H
#define REPLICATIONMANAGER_H

class Food;

class ReplicationManager
{

public:
    enum ReplicationAction
    {
        RA_CREATE,
        RA_UPDATE,
        RA_DESTROY
    };

    ReplicationManager() = default;
    ~ReplicationManager() = default;

    ReplicationManager(class Game *game);

    void read(InputStream &inStream);

private:
    void readAndCreate(InputStream &inputStream);
    void readAndUpdate(InputStream &inputStream);
    void readAndDestroy(InputStream &inputStream);

    class Game *mGame;
};

#endif