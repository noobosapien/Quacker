#include "../headers/gamepch.h"

CircleRenderComponent::CircleRenderComponent(class Actor *owner, Renderer *renderer, int drawOrder) : RenderComponent(owner,
                                                                                                                      renderer,
                                                                                                                      drawOrder)
{
    mRenderer->insertObject(this, mDrawOrder);
    mShader = mRenderer->getShader("circledebug");
}

CircleRenderComponent::~CircleRenderComponent()
{
    mRenderer->removeObject(this);
}

void CircleRenderComponent::draw()
{
    if (mShader)
    {
        mShader->setActive();

        glm::mat4 model = glm::mat4(1.f);

        model = mOwner->getWorldTransform();

        mShader->setMatrixUniform("u_model", model);
        mShader->setMatrixUniform("u_viewproj", mRenderer->getCamera()->getViewProj());
        mShader->setVec3Uniform("u_position", glm::vec3(MathUtils::changeWindowToGameCoords(mOwner->getPosition()), 0.0));
        mShader->setVec2Uniform("u_res", mRenderer->WIN_RES);
        mShader->setFloatUniform("u_size", mOwner->getScale() / 2);
    }
}

void CircleRenderComponent::update(float delta)
{
}