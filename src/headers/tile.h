#ifndef TILE_H
#define TILE_H

class Tile : public Component
{

public:
    Tile(class Actor *owner, class Texture *texture, int x, int y, int width, int height);
    virtual ~Tile();

    void draw(class Shader *shader);

private:
    int mX;
    int mY;
    int mWidth;
    int mHeight;

    class Texture *mTexture = nullptr;
};

#endif