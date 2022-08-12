#ifndef CAMERA_H
#define CAMERA_H

class Camera
{

public:
    // Camera(float left = 0.f, float right = 713.6f, float bot = 713.6f, float top = 0.f);
    Camera(float left = -1.f, float right = 1.f, float bot = -1.f, float top = 1.f);
    ~Camera();

    glm::mat4 &getViewProj() { return mViewProj; }
    glm::mat4 &getView() { return mView; }
    glm::mat4 &getProjection() { return mProjection; }

    glm::mat4 &getUIProjection() { return mUIProjection; }
    glm::mat4 &getUIViewProj() { return mUIViewProj; }

    void setPosition(glm::vec3 pos)
    {
        mPosition = pos;
        recomputeViewProj();
    }
    void setRotation(float rot)
    {
        mRotation = rot;
        recomputeViewProj();
    }

    void addViewportVertices(float left, float right, float top, float bot);

private:
    void recomputeViewProj();

    glm::mat4 mViewProj;
    glm::mat4 mView;
    glm::mat4 mProjection;

    glm::mat4 mUIProjection;
    glm::mat4 mUIViewProj;

    glm::vec3 mPosition;
    float mRotation;

    float mLeft;
    float mRight;
    float mTop;
    float mBot;
};

#endif