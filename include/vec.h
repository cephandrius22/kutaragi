//
// Created by jvwri on 12/7/2022.
//

#ifndef KUTARAGI_VEC_H
#define KUTARAGI_VEC_H

class Vec3 {
public:
    double x, y, z;

    Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& v) {
        return Vec3(this->x + v.x, this->y + v.y, this->z + v.z);
    }

    Vec3 operator-(const Vec3& v) {
        return Vec3(this->x - v.x, this->y - v.y, this->z - v.z);
    }

    Vec3 operator*(const Vec3& v) {
        return Vec3(this->x * v.x, this->y * v.y, this->z * v.z);
    }

    Vec3 operator*(double scalar) {
        return Vec3(this->x * scalar, this->y * scalar, this->z * scalar);
    }
};



#endif //KUTARAGI_VEC_H
