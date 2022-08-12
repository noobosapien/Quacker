#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

class GameLevel
{
public:
    GameLevel(Game* game);
    ~GameLevel();

    void load(const char *file, unsigned int levelWidth, unsigned int levelHeight);

    void addObject(class Object *object);
    void removeObject(class Object *object);

private:
    void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
    std::vector<class Object *> mObjects;
    Game *mGame;
};

#endif