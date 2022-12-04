#include "../headers/gamepch.h"

LightningComponent::LightningComponent(class Actor *owner,
                                       class Renderer *renderer,
                                       int drawOrder) : RenderComponent(owner, renderer, drawOrder),
                                                        mTexWidth(0),
                                                        mTexHeight(0),
                                                        mTime(0.f)
{
    mRenderer->insertObject(this, mDrawOrder);
    mShader = mRenderer->getShader("lightning");
}

LightningComponent::~LightningComponent()
{
    mRenderer->removeObject(this);
}

void LightningComponent::update(float delta)
{
    if (mTime < 4.f)
        mTime += delta;
    else
        mTime = 0.f;
}

void LightningComponent::draw()
{
    if (mShader)
    {
        mShader->setActive();

        // glm::mat4 model = glm::mat4(1.f);

        // model = mOwner->getWorldTransform();

        // mShader->setMatrixUniform("u_model", model);
        // mShader->setMatrixUniform("u_viewproj", mRenderer->getCamera()->getViewProj());

        float mScale = 1.;
        float mRotation = 90.f;

        glm::mat4 model = glm::mat4(1.f);
        // model = glm::translate(model, glm::vec3(mPosition.x, mPosition.y, 0.f));
        model = glm::rotate(model, glm::radians(mRotation), glm::vec3(0.f, 0.f, 1.f));
        model = glm::scale(model, glm::vec3(1.f, mScale, 1.f));

        mShader->setFloatUniform("u_time", mTime);
        mShader->setMatrixUniform("u_model", model);
        mShader->setMatrixUniform("u_viewproj", mRenderer->getCamera()->getViewProj());
    }
}