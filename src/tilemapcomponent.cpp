#include "headers/gamepch.h"

TilemapComponent::TilemapComponent(Actor *owner, Texture *texture, int tileWidth, int tileHeight, int tilesHorz, int tilesVert)
    : Component(owner), mTexture(texture), tileNum(tilesHorz * tilesVert)
{
    loadTiles(tileWidth, tileHeight, tilesHorz, tilesVert);
}

TilemapComponent::~TilemapComponent()
{
    for (auto horzTile : mTiles)
    {
        for (auto tile : horzTile)
        {
            this->removeTile(tile);
        }
    }
}

void TilemapComponent::draw(class Shader *shader)
{
    glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto horzTile : mTiles)
    {
        for (auto tile : horzTile)
        {
            tile->draw(shader);
        }
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    shader->setActive();

    glm::mat4 model = glm::mat4(1.0f);

    model = mOwner->getWorldTransform();

    // projection = glm::perspective(glm::radians(45.0f), ((float)Game::WIN_WIDTH / (float)Game::WIN_HEIGHT), 0.1f, 100.0f);

    shader->setMatrixUniform("u_model", model);
    shader->setMatrixUniform("u_viewproj", mOwner->getGame()->getCamera()->getViewProj());

    mTilemap->setActive();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void TilemapComponent::SetWidthAndHeight(int _width, int _height)
{
    this->width = _width;
    this->height = _height;
}

void TilemapComponent::SetTileNum(int num)
{
    tileNum = num;
}

void TilemapComponent::removeTile(class Tile *tile)
{

    for (auto horzTiles : mTiles)
    {
        auto iter = std::find(horzTiles.begin(), horzTiles.end(), tile);
        if (iter != horzTiles.end())
        {
            horzTiles.erase(iter);
        }
    }

    mTiles.clear();
}

void TilemapComponent::loadTiles(int tileWidth, int tileHeight, int tilesHorz, int tilesVert)
{
    int curHorz = 0;
    int curVert = 0;

    glGenFramebuffers(1, &mFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
    mTilemap = mOwner->getGame()->getTexture("src/assets/textures/bg.png");
    mTilemap->setActive();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTilemap->getId(), 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    while (curVert < tilesVert)
    {

        mTiles.push_back(std::vector<Tile *>());

        while (curHorz < tilesHorz)
        {

            int x = curHorz * tileWidth;
            int y = curVert * tileHeight;

            Tile *tile = new Tile(mOwner, mTexture, x, y, tileWidth, tileHeight);
            mTiles[curVert].push_back(tile);
            curHorz++;
        }

        curHorz = 0;
        curVert++;
    }
}