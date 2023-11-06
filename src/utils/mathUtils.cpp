#include "../headers/gamepch.h"

namespace MathUtils
{

    glm::vec2 changeWindowToGameCoords(const glm::vec2 &v)
    {
        glm::vec2 ret(v);

        // ret.x *= (Renderer::GAME_WIDTH / 2)

        // ret.x -= (Renderer::GAME_WIDTH / 2);
        // ret.y -= (Renderer::GAME_HEIGHT / 2);
        // ret.x /= (Renderer::GAME_WIDTH / 2);
        // ret.y /= -(Renderer::GAME_HEIGHT / 2);

        ret.x += 1;
        ret.y += 1;
        ret.x /= 2;
        ret.y /= 2;

        return ret;
    }

    // float angle(const glm::vec2 &l, const glm::vec2 &r)
    // {
    //     float sqMagL = l.x * l.x + l.y * l.y;
    //     float sqMagR = r.x * r.x + r.y * r.y;

    //     if (sqMagL < VEC3_EPSILON || sqMagR < VEC3_EPSILON)
    //     {
    //         return 0.0f;
    //     }

    //     float dot = l.x * r.x + l.y * r.y;
    //     float len = sqrtf(sqMagL) * sqrtf(sqMagR);
    //     return acosf(dot / len);
    // }

    // float angle(const glm::vec3 &l, const glm::vec3 &r)
    // {
    //     float sqMagL = l.x * l.x + l.y * l.y + l.z * l.z;
    //     float sqMagR = r.x * r.x + r.y * r.y + r.z * r.z;

    //     if (sqMagL < VEC3_EPSILON || sqMagR < VEC3_EPSILON)
    //     {
    //         return 0.0f;
    //     }

    //     float dot = l.x * r.x + l.y * r.y + l.z * r.z;
    //     float len = sqrtf(sqMagL) * sqrtf(sqMagR);
    //     return acosf(dot / len);
    // }

    // glm::vec3 lerp(const glm::vec3 &s, const glm::vec3 &e, float t)
    // {
    //     return glm::vec3(
    //         s.x + (e.x - s.x) * t,
    //         s.y + (e.y - s.y) * t,
    //         s.z + (e.z - s.z) * t);
    // }

    // glm::vec3 slerp(const glm::vec3 &s, const glm::vec3 &e, float t)
    // {
    //     if (t < 0.01f)
    //     {
    //         return lerp(s, e, t);
    //     }

    //     glm::vec3 from = glm::normalize(s);
    //     glm::vec3 to = glm::normalize(e);

    //     float theta = angle(from, to);
    //     float sin_theta = sinf(theta);

    //     float a = sinf((1.0f - t) * theta) / sin_theta;
    //     float b = sinf(t * theta) / sin_theta;

    //     return from * a + to * b;
    // }

    // glm::vec3 nlerp(const glm::vec3 &s, const glm::vec3 &e, float t)
    // {
    //     glm::vec3 linear(
    //         s.x + (e.x - s.x) * t,
    //         s.y + (e.y - s.y) * t,
    //         s.z + (e.z - s.z) * t);

    //     return glm::normalize(linear);
    // }
}