#ifndef STAR_BG_COMPONENT_H
#define STAR_BG_COMPONENT_H

struct Star
{
    float mScale;
    float mRotation;
    glm::vec3 mPosition;

    float mDuration;
    float mOffsetDuration;
    float mTotalDuration;

    bool mRotDirection;

    float mRotSpeed;
    float mToScale;
    int mVertSpeed;

    class Texture *mTexture;

    void draw(Shader *shader, Renderer *renderer)
    {
        if (shader)
        {
            shader->setActive();

            glm::mat4 model = glm::mat4(1.f);

            // create a model matrix from pos, rot scale

            model = glm::translate(model, glm::vec3(mPosition.x, mPosition.y, 0.f));
            model = glm::rotate(model, glm::radians(mRotation), glm::vec3(0.f, 0.f, 1.f));
            model = glm::scale(model, glm::vec3(mScale, mScale, mScale));

            shader->setMatrixUniform("u_model", model);
            shader->setMatrixUniform("u_viewproj", renderer->getCamera()->getViewProj());

            mTexture->setActive();

            renderer->manualDrawTriangles();
        }
    }
};

class StarBGComponent : public RenderComponent
{

public:
    StarBGComponent(class Actor *owner, class Renderer *renderer, Texture *texture, unsigned int amount, int drawOrder = 100);
    virtual ~StarBGComponent();

    virtual void draw() override;
    virtual void update(float delta) override;

private:
    std::vector<Star *> mStars;
};

#endif