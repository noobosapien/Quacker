#include "../headers/gamepch.h"

Camera::Camera(float left, float right, float bot, float top) : mPosition(0.f), mRotation(0.f),
                                                                mLeft(left), mRight(right), mTop(top), mBot(bot)
{
    // mProjection = glm::ortho(mLeft, mRight, mBot, mTop, -1.f, 10.f);
    mProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 100.0f);
    mPosition = glm::vec3(0, 0, 1);
    mUIProjection = mProjection;
    mView = glm::mat4(1.f);

    recomputeViewProj();
}

Camera::~Camera() {}

void Camera::recomputeViewProj()
{
    // glm::mat4 translate = glm::translate(glm::mat4(1.f), mPosition);
    // translate = glm::rotate(translate, mRotation, glm::vec3(0.f, 0.f, 1.f));

    // mView = glm::inverse(translate);

    mView = glm::lookAt(mPosition, mPosition + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    mViewProj = mProjection * mView;
    // mViewProj = mView;
    mUIViewProj = mUIProjection;
}

void Camera::addViewportVertices(float left, float right, float bot, float top)
{
    mLeft += left;
    mRight += right;
    mTop += top;
    mBot += bot;

    // mProjection = glm::ortho(mLeft, mRight, mBot, mTop, -1.f, 10.f);
    mProjection = glm::perspective(glm::radians(90.0f), 1.f, 0.1f, 100.0f);

    recomputeViewProj();
}