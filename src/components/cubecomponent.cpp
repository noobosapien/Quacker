#include "../headers/gamepch.h"

CubeComponent::CubeComponent(Actor *owner, Renderer *renderer, int drawOrder) : RenderComponent(owner, renderer, drawOrder),
                                                                                mTexture(nullptr),
                                                                                mTexWidth(0),
                                                                                mTexHeight(0)
{
    mRenderer->insertObject(this, mDrawOrder);
    mShader = mRenderer->getShader("cube");
}

CubeComponent::~CubeComponent()
{
    mRenderer->removeObject(this);
}

void CubeComponent::draw()
{

    if (mTexture && mShader)
    {
        mShader->setActive();

        glm::mat4 model = glm::mat4(1.f);

        model = mOwner->getWorldTransform();

        mShader->setMatrixUniform("u_model", model);
        mShader->setMatrixUniform("u_viewproj", mRenderer->getCamera()->getViewProj());

        mTexture->setActive();
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void CubeComponent::setTexture(class Texture *texture)
{
    mTexture = texture;

    mTexWidth = texture->getWidth();
    mTexHeight = texture->getHeight();
}