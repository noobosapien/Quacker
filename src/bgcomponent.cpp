#include "headers/gamepch.h"

BGComponent::BGComponent(class Actor *owner, int drawOrder) : Component(owner), mScrollSpeed(0.f)
{
}

BGComponent::~BGComponent()
{
    for (auto bg : mBGTextures)
    {
        delete bg;
    }
}

void BGComponent::setScreenSize(glm::vec2 size)
{
    mScreenSize = size;
}

void BGComponent::setBGTextures(std::vector<Texture *> textures)
{
    int count = 0;

    for (auto tex : textures)
    {
        BGTexture *temp = new BGTexture();

        temp->mTexture = tex;
        temp->mOffset.x = 0;
        temp->mOffset.y = count * mScreenSize.y;

        mBGTextures.emplace_back(temp);
        count++;
    }
}

void BGComponent::setScrollSpeed(float speed)
{
    mScrollSpeed = speed;
}

void BGComponent::update(float delta)
{
    Component::update(delta);

    for (auto bg : mBGTextures)
    {
        bg->mOffset.y += mScrollSpeed * delta;

        if (bg->mOffset.y < -mScreenSize.y)
        {
            bg->mOffset.y = (mBGTextures.size() - 1) * mScreenSize.y - 1;
        }
    }
}

void BGComponent::draw(class Shader *shader)
{
    shader->setActive();

    for (auto bg : mBGTextures)
    {

        glm::mat4 model = glm::mat4(1.f);

        model = glm::translate(model, glm::vec3(bg->mOffset.x, bg->mOffset.y, 0.f));
        model = glm::scale(model, glm::vec3(mScreenSize.x, mScreenSize.y, 1.f));

        // projection = glm::perspective(glm::radians(45.0f), ((float)Game::WIN_WIDTH / (float)Game::WIN_HEIGHT), 0.1f, 100.0f);

        shader->setMatrixUniform("u_model", model);
        shader->setMatrixUniform("u_viewproj", mOwner->getGame()->getCamera()->getViewProj());

        bg->mTexture->setActive();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
}
