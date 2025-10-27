#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "math.hpp"
#include "color.hpp"
struct Triangle {
    Vector3 v[3];//顶点
    Vector3 n[3];//法线
    Vector2 uv[3];//纹理坐标
    Color c[3];//颜色

     Triangle(const Vector3& v0, const Vector3& v1, const Vector3& v2,
              const Vector3& n0, const Vector3& n1, const Vector3& n2,
              const Vector2& uv0, const Vector2& uv1, const Vector2& uv2,
              const Color& c0, const Color& c1, const Color& c2) :
        v{ v0, v1, v2 }, n{ n0, n1, n2 }, uv{ uv0, uv1, uv2 }, c{ c0, c1, c2 } {}
};

#endif