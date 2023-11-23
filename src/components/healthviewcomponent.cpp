#include "../headers/gamepch.h"

HealthViewComponent::HealthViewComponent(Actor *owner, class Renderer *renderer, class HPComponent *hp,
                                         bool isEnemy, int drawOrder)
    : RenderComponent(owner, renderer, drawOrder), mIsEnemy(isEnemy), mHP(hp)
{
    mRenderer->insertObject(this, mDrawOrder);
    mShader = mRenderer->getShader("health");
}

HealthViewComponent::~HealthViewComponent()
{
    mRenderer->removeObject(this);
}

void HealthViewComponent::draw()
{
    if (mShader)
    {
        mShader->setActive();

        glm::mat4 model = glm::mat4(1.f);

        model = mOwner->getWorldTransform();

        mShader->setVec3Uniform("u_pos", glm::vec3(MathUtils::changeWindowToGameCoords(mOwner->getPosition()), 0.0));
        mShader->setVec2Uniform("u_res", mRenderer->WIN_RES);

        glm::vec3 move;

        if (mIsEnemy)
        {
            move = glm::vec3(0., -5 * mOwner->getScale(), 0.);
            model = glm::translate(model, move);
        }
        else
        {
            move = glm::vec3(0., 5 * mOwner->getScale(), 0.);
            model = glm::translate(model, move);
        }

        mShader->setVec3Uniform("u_pos",
                                glm::vec3(MathUtils::changeWindowToGameCoords(mOwner->getPosition()),
                                          0.0));

        mShader->setMatrixUniform("u_model", model);
        mShader->setMatrixUniform("u_viewproj", mRenderer->getCamera()->getViewProj());
    }
}