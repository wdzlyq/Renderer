#ifndef MATH_HPP
#define MATH_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <iomanip>

struct Vector3 {
    float x, y, z;

    Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}
    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }
    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }
    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }
    Vector3 operator/(float scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }
     float dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
     Vector3 cross(const Vector3& other) const {
        return Vector3(y * other.z - z * other.y,
                       z * other.x - x * other.z,
                       x * other.y - y * other.x);
    }
     float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }
     Vector3 normalize() const {
        return *this / length();
    }
     Vector3 operator-() const {
        return Vector3(-x, -y, -z);
    }
     bool operator==(const Vector3& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
     bool operator!=(const Vector3& other) const {
        return !(*this == other);
    }
    friend std::ostream& operator<<(std::ostream& os, const Vector3& vec) {
        os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
        return os;
    }
};

struct Vector2 {
    float x, y;
    Vector2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
     Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }
     Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }
     Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }
     Vector2 operator/(float scalar) const {
        return Vector2(x / scalar, y / scalar);
    }
     float dot(const Vector2& other) const {
        return x * other.x + y * other.y;
    }
     float length() const {
        return std::sqrt(x * x + y * y);
    }
     Vector2 normalize() const {
        return *this / length();
    }
     Vector2 operator-() const {
        return Vector2(-x, -y);
    }
     bool operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }
     bool operator!=(const Vector2& other) const {
        return !(*this == other);
    }
    friend std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
        os << "(" << vec.x << ", " << vec.y << ")";
        return os;
    }

};
struct Matrix4x4 {
    float m[4][4];
    Matrix4x4(float diag = 1.0f) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                m[i][j] = (i == j) ? diag : 0.0f;
            }
        }
    }
     Matrix4x4 operator*(const Matrix4x4& other) const {
        Matrix4x4 result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result.m[i][j] = 0.0f;
                for (int k = 0; k < 4; ++k) {
                    result.m[i][j] += m[i][k] * other.m[k][j];
                }
            }
        }
        return result;
    }
    Vector3 operator*(const Vector3& v) const {
        float x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3];
        float y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3];
        float z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3];
        float w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3];
        
        if (w != 0) {
            return Vector3(x / w, y / w, z / w); // 透视除法
        }
        return Vector3(x, y, z); // 如果w为0，不进行除法
    }
    //平移矩阵
    static Matrix4x4 translation(float tx, float ty, float tz) {
        Matrix4x4 result(1.0f);
        result.m[0][3] = tx;
        result.m[1][3] = ty;
        result.m[2][3] = tz;
        return result;
    }
    //缩放矩阵
    static Matrix4x4 scaling(float sx, float sy, float sz) {
        Matrix4x4 result(1.0f);
        result.m[0][0] = sx;
        result.m[1][1] = sy;
        result.m[2][2] = sz;
        return result;
    }
    //绕x轴旋转矩阵
    static Matrix4x4 rotationX(float angle) {
        Matrix4x4 result(1.0f);
        float cosA = std::cos(angle);
        float sinA = std::sin(angle);
        result.m[1][1] = cosA;
        result.m[1][2] = -sinA;
        result.m[2][1] = sinA;
        result.m[2][2] = cosA;
        return result;
    }
    //绕y轴旋转矩阵
    static Matrix4x4 rotationY(float angle) {
        Matrix4x4 result(1.0f);
        float cosA = std::cos(angle);
        float sinA = std::sin(angle);
        result.m[0][0] = cosA;
        result.m[0][2] = sinA;
        result.m[2][0] = -sinA;
        result.m[2][2] = cosA;
        return result;
    }
    //绕z轴旋转矩阵
    static Matrix4x4 rotationZ(float angle) {
        Matrix4x4 result(1.0f);
        float cosA = std::cos(angle);
        float sinA = std::sin(angle);
        result.m[0][0] = cosA;
        result.m[0][1] = -sinA;
        result.m[1][0] = sinA;
        result.m[1][1] = cosA;
        return result;
    }
    //透视投影矩阵
    static Matrix4x4 perspective(float fovy, float aspect, float near, float far) {
        Matrix4x4 result(0.0f);
        float tanHalfFovy = std::tan(fovy / 2.0f);
        result.m[0][0] = 1.0f / (aspect * tanHalfFovy);
        result.m[1][1] = 1.0f / (tanHalfFovy);
        result.m[2][2] = -(far + near) / (far - near);
        result.m[2][3] = -2.0f * far * near / (far - near);
        result.m[3][2] = -1.0f;
        return result;
    }
    //视图矩阵
    static Matrix4x4 lookAt(const Vector3& eye, const Vector3& target, const Vector3& up) {
        Vector3 f = (target - eye).normalize();
        Vector3 u = up.normalize();
        Vector3 s = f.cross(u).normalize();
        u = s.cross(f);

        Matrix4x4 mat;
        mat.m[0][0] = s.x;  mat.m[0][1] = s.y;  mat.m[0][2] = s.z;  mat.m[0][3] = -s.dot(eye);
        mat.m[1][0] = u.x;  mat.m[1][1] = u.y;  mat.m[1][2] = u.z;  mat.m[1][3] = -u.dot(eye);
        mat.m[2][0] = -f.x; mat.m[2][1] = -f.y; mat.m[2][2] = -f.z; mat.m[2][3] = f.dot(eye);
        mat.m[3][0] = 0;    mat.m[3][1] = 0;    mat.m[3][2] = 0;    mat.m[3][3] = 1;
        return mat;
    }

};
#endif

