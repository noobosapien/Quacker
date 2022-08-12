#ifndef TILE_MAP_COMPONENT_H
#define TILE_MAP_COMPONENT_H

class TilemapComponent : public Component
{
public:
    TilemapComponent(Actor *owner, class Texture *texture,
                     int tileWidth = 0, int tileHeight = 0, int tilesHorz = 0, int tilesVert = 0);
    ~TilemapComponent();
    virtual void draw(class Shader *shader);
    void SetWidthAndHeight(int _width, int _height);

    void removeTile(class Tile *tile);

private:
    int width;
    int height;
    int tileNum;

    unsigned int mFBO;
    class Texture *mTexture;
    class Texture *mTilemap;

    void SetTileNum(int num);
    void loadTiles(int tileWidth, int tileHeight, int texWidth, int tilesVert);

    std::vector<std::vector<class Tile *>> mTiles;
};

#endif