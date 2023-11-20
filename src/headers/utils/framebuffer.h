#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

class Framebuffer
{
public:
    Framebuffer(Renderer *renderer);
    ~Framebuffer();

    void attachShader();
    void draw();
    void resizeTexture();

    inline void bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, mId);
    }

    inline void unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    inline GLuint getTextureBuffer()
    {
        return mTextureColorBuffer;
    }

private:
    GLuint mId;
    GLuint mTextureColorBuffer;
    GLuint mRBO;

    Renderer *mRenderer;
    Shader *mShader;
};

#endif