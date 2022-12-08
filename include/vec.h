#ifndef KUTARAGI_VEC_H
#define KUTARAGI_VEC_H

#include <array>

class Vec3 {
public:
    std::array<float, 3> e;

    Vec3() : e{0, 0, 0} {}
    Vec3(float x, float y, float z) : e{x, y, z} {}

    Vec3 operator+(const Vec3& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    Vec3 operator-(const Vec3& v) {
        e[0] -= v.e[0];
        e[1] -= v.e[1];
        e[2] -= v.e[2];
        return *this;
    }

    /* I don't know that this type of multiplication is ever used. */
    Vec3 operator*(const Vec3& v) {
        e[0] *= v.e[0];
        e[1] *= v.e[1];
        e[2] *= v.e[2];
        return *this;
    }

    Vec3 operator*(float scalar) {
        e[0] *= scalar;
        e[1] *= scalar;
        e[2] *= scalar;
        return *this;
    }

    bool operator==(const Vec3& v) const {
        return this->e == v.e;
    }

    float operator[](int i) {
        return e[i];
    }
};

using Point3 = Vec3;

float dot(const Vec3& a, const Vec3& b) {
    return a.e[0] * b.e[0] + a.e[1] * b.e[1] + a.e[2] * b.e[2];
}

class Vec4 {
public:
    std::array<float, 4> e{};

    Vec4() : e{0, 0, 0, 0} {}
    Vec4(float x, float y, float z, float w) : e{x, y, z, w} {}

    Vec4(Vec3 vec, float w) {
        this->e[0] = vec.e[0];
        this->e[1] = vec.e[1];
        this->e[2] = vec.e[2];
        this->e[3] = w;
    }

    bool operator==(const Vec4& v) const {
        return this->e == v.e;
    }
};

#endif //KUTARAGI_VEC_H
