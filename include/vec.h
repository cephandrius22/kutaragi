//
// Created by jvwri on 12/7/2022.
//

#ifndef KUTARAGI_VEC_H
#define KUTARAGI_VEC_H

class Vec3 {
public:
    float x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& v) {
        return Vec3(this->x + v.x, this->y + v.y, this->z + v.z);
    }

    Vec3 operator-(const Vec3& v) {
        return Vec3(this->x - v.x, this->y - v.y, this->z - v.z);
    }

    Vec3 operator*(const Vec3& v) {
        return Vec3(this->x * v.x, this->y * v.y, this->z * v.z);
    }

    Vec3 operator*(float scalar) {
        return Vec3(this->x * scalar, this->y * scalar, this->z * scalar);
    }

    bool operator==(const Vec3& v) {
        return this->x == v.x && this->y == v.y && this->z == v.z;
    }
};

using Point3 = Vec3;

float dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

class Vec4 {
public:
    float x, y, z, w;

    Vec4() : x(0), y(0), z(0), w(0) {}
    Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    Vec4(Vec3 vec, float w) {
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
        this->w = w;
    }

    bool operator==(const Vec4& v) {
        return this->x == v.x && this->y == v.y && this->z == v.z && this->w == v.w;
    }
};

#endif //KUTARAGI_VEC_H
