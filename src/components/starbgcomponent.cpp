#include "../headers/gamepch.h"

StarBGComponent::StarBGComponent(Actor *owner, Renderer *renderer, Texture *texture, unsigned int amount,
                                 int drawOrder) : RenderComponent(owner, renderer, drawOrder)
{
    mRenderer->insertObject(this, mDrawOrder);
    mShader = mRenderer->getShader("sprite");

    for (int i = 0; i < amount; i++)
    {
        // create a star
        // random pos between 0. and 1.
        // rot is 0
        // duration is 0.
        // random rot direction
        // scale starts with zero
        // push it to mStars

        float posX = -1.f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2);
        float posY = -1.f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2);

        bool rotDir = 0 + (rand() % (1 - 0 + 1)) == 1;
        float offDur = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2);
        float totalDuration = 6.f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 9.f);

        float rotSpeed = 30.f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 70.f);
        float toScale = 0.02 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 0.04);

        int vertSpeed = 0 + (rand() % (1 - 0 + 1)) == 1 + (rand() % (1 - 0 + 1)) == 1;

        Star *star = new Star{
            0.f,
            0.f,
            glm::vec2(posX, posY),
            0.f,
            offDur,
            totalDuration,
            rotDir,
            rotSpeed,
            toScale,
            vertSpeed,
            texture};

        mStars.push_back(star);
    }
}

StarBGComponent::~StarBGComponent()
{
    mStars.clear();
    mRenderer->removeObject(this);
}

void StarBGComponent::draw()
{
    // for each star draw by giving the shader and the renderer
    for (int i = 0; i < mStars.size(); i++)
    {
        mStars[i]->draw(mShader, mRenderer);
    }
}

void StarBGComponent::update(float delta)
{
    // for each star update the rotation and scale depending on duration
    // if duration is more than a specific point make the duration zero
    // give that star a different position and start from the begining

    for (int i = 0; i < mStars.size(); i++)
    {
        Star *star = mStars[i];

        star->mDuration += delta;

        switch (star->mVertSpeed)
        {
        case 0:
            star->mPosition.y -= 0.02 * delta;
            break;

        case 1:
            star->mPosition.y -= 0.1 * delta;
            break;

        case 2:
            star->mPosition.y -= 0.2 * delta;
            break;

        default:
            break;
        }

        if (star->mRotDirection)
        {
            star->mRotation += star->mRotSpeed * delta;
        }
        else
        {
            star->mRotation -= star->mRotSpeed * delta;
        }

        if (star->mDuration < star->mTotalDuration + star->mOffsetDuration && star->mDuration > star->mOffsetDuration)
        {
            if ((star->mDuration - star->mOffsetDuration) < star->mTotalDuration * 0.25)
            {
                star->mScale = Curves::f_linearInterpolate(0.0, star->mToScale, (star->mDuration - star->mOffsetDuration) / (star->mTotalDuration * 0.25));
            }
            else if ((star->mDuration - star->mOffsetDuration) >= star->mTotalDuration * 0.25 && (star->mDuration - star->mOffsetDuration) < (star->mTotalDuration * 0.5))
            {
                star->mScale = Curves::f_linearInterpolate(star->mToScale, 0.0, (star->mDuration - star->mOffsetDuration - star->mTotalDuration * 0.25) / (star->mTotalDuration * 0.25));
            }
            else if ((star->mDuration - star->mOffsetDuration) >= star->mTotalDuration * 0.5 && (star->mDuration - star->mOffsetDuration) < (star->mTotalDuration * 0.75))
            {
                star->mScale = Curves::f_linearInterpolate(0.0, star->mToScale, (star->mDuration - star->mOffsetDuration - star->mTotalDuration * 0.5) / (star->mTotalDuration * 0.25));
            }
            else
            {
                star->mScale = Curves::f_linearInterpolate(star->mToScale, 0.0, (star->mDuration - star->mOffsetDuration - star->mTotalDuration * 0.75) / 3.0);
            }
        }
        else if (star->mDuration >= star->mTotalDuration + star->mOffsetDuration)
        {
            float posX = -1.f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2.0);
            float posY = -1.f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2.0);

            float offDur = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2.0);

            float totalDuration = 6.f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 9.f);

            float rotSpeed = 30.f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 70.f);
            float toScale = 0.02 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 0.06);

            int vertSpeed = 0 + (rand() % (1 - 0 + 1)) == 1 + (rand() % (1 - 0 + 1)) == 1;

            star->mPosition = glm::vec2(posX, posY);
            star->mScale = 0.f;
            star->mRotation = 0.f;
            star->mOffsetDuration = offDur;
            star->mTotalDuration = totalDuration;
            star->mRotDirection = 0 + (rand() % (1 - 0 + 1)) == 1;
            star->mDuration = 0.f;
            star->mRotSpeed = rotSpeed;
            star->mToScale = toScale;
            star->mVertSpeed = vertSpeed;
        }
    }
}