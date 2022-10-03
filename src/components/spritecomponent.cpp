#include "../headers/gamepch.h"

SpriteComponent::SpriteComponent(Actor *owner, Renderer *renderer, int drawOrder) : RenderComponent(owner, renderer, drawOrder),
                                                                                    mTexture(nullptr),
                                                                                    mTexWidth(0),
                                                                                    mTexHeight(0)
{
    mRenderer->insertObject(this, mDrawOrder);
    mShader = mRenderer->getShader("sprite");
}

SpriteComponent::~SpriteComponent()
{
    mRenderer->removeObject(this);
}

void SpriteComponent::draw()
{

    if (mTexture && mShader)
    {
        mShader->setActive();

        glm::mat4 model = glm::mat4(1.f);

        model = mOwner->getWorldTransform();

        mShader->setMatrixUniform("u_model", model);
        mShader->setMatrixUniform("u_viewproj", mRenderer->getCamera()->getViewProj());

        mTexture->setActive();
    }
}

void SpriteComponent::setTexture(class Texture *texture)
{
    mTexture = texture;

    mTexWidth = texture->getWidth();
    mTexHeight = texture->getHeight();
}