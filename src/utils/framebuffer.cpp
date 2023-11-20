#include "../headers/gamepch.h"

Framebuffer::Framebuffer(Renderer *renderer) : mRenderer(renderer), mShader(nullptr)
{
    glGenFramebuffers(1, &mId);
    glBindFramebuffer(GL_FRAMEBUFFER, mId);

    glGenTextures(1, &mTextureColorBuffer);
    glBindTexture(GL_TEXTURE_2D, mTextureColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Renderer::WIN_RES.x, Renderer::WIN_RES.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTextureColorBuffer, 0);

    glGenRenderbuffers(1, &mRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, mRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, Renderer::WIN_RES.x, Renderer::WIN_RES.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mRBO);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Error: Framebuffer is not complete." << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Framebuffer::~Framebuffer()
{
}

void Framebuffer::attachShader()
{
    if (!mShader)
    {
        mShader = mRenderer->getShader("framebuffer");
    }
}

void Framebuffer::draw()
{
    if (mShader)
    {
        mShader->setActive();

        glDisable(GL_DEPTH_TEST);
        glClearColor(0., 1., 1., 1.);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, NULL);
        glBindTexture(GL_TEXTURE_2D, mTextureColorBuffer);
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
}

void Framebuffer::resizeTexture()
{
    bind();
    glBindTexture(GL_TEXTURE_2D, mTextureColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Renderer::WIN_RES.x, Renderer::WIN_RES.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTextureColorBuffer, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, mRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, Renderer::WIN_RES.x, Renderer::WIN_RES.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mRBO);
    unbind();
}