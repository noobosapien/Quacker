#ifndef BGCOMPONENT_H
#define BGCOMPONENT_H

class BGComponent : public Component
{

public:
    BGComponent(class Actor *owner, int drawOrder = 1);
    virtual ~BGComponent();

    void setScreenSize(glm::vec2 size);
    void setBGTextures(std::vector<Texture *> textures);
    void setScrollSpeed(float speed);

    void update(float delta) override;
    void draw(class Shader *shader);

private:
    struct BGTexture
    {
        Texture *mTexture;
        glm::vec2 mOffset;
    };

    std::vector<BGTexture *> mBGTextures;
    glm::vec2 mScreenSize;
    float mScrollSpeed;
};

#endif
