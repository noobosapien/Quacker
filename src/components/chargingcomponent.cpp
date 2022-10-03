#include "../headers/gamepch.h"

ChargingComponent::ChargingComponent(class Actor *owner, Renderer *renderer, int drawOrder) : RenderComponent(owner,
                                                                                                              renderer,
                                                                                                              drawOrder),
                                                                                              mShow(false), mIntensity(1.76432f)
{
    mRenderer->insertObject(this, mDrawOrder);
    mShader = mRenderer->getShader("charging");
}

ChargingComponent::~ChargingComponent()
{
    mRenderer->removeObject(this);
}

void ChargingComponent::draw()
{
    if (mShader && mShow)
    {
        mShader->setActive();

        glm::mat4 model = glm::mat4(1.f);

        model = mOwner->getWorldTransform();

        mShader->setMatrixUniform("u_model", model);
        mShader->setMatrixUniform("u_viewproj", mRenderer->getCamera()->getViewProj());
        mShader->setFloatUniform("u_time", mOwner->getGame()->getCurrentTime());
        mShader->setFloatUniform("u_intensity", mIntensity);
    }
}

void ChargingComponent::update(float delta)
{
}