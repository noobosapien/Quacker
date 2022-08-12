#include "headers/gamepch.h"

Tile::Tile(class Actor *owner, class Texture *texture, int x, int y, int width, int height)
    : Component(owner), mX(x), mY(y), mWidth(width), mHeight(height), mTexture(texture)
{
}

Tile::~Tile()
{
}

void Tile::draw(class Shader *shader)
{
    if (mTexture)
    {
        shader->setActive();

        glm::mat4 model = glm::mat4(1.f);

        model = mOwner->getWorldTransform();

        // projection = glm::perspective(glm::radians(45.0f), ((float)Game::WIN_WIDTH / (float)Game::WIN_HEIGHT), 0.1f, 100.0f);

        shader->setMatrixUniform("u_model", model);
        shader->setMatrixUniform("u_viewproj", mOwner->getGame()->getCamera()->getViewProj());

        mTexture->setActive();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
}