#ifndef KUTARAGI_MATRIX_H
#define KUTARAGI_MATRIX_H

#include "vec.h"
#include <array>
#include <math.h>
#include <iostream>

const float PI = 3.14159;

class Mat4
{
public:
    // NOTE: these values are stored in row-major order
    std::array<float, 4 * 4> values{};

    Mat4() = default;
    Mat4(std::array<float, 16> values) : values(values) {}

    Vec4 operator*(const Vec4 &vec)
    {
        Vec4 result{};
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                result.e[i] += this->values[i * 4 + j] * vec.e[j];
            }
        }

        return result;
    }

    Mat4 operator*(const Mat4 &mat)
    {
        Mat4 result{};
        /* There has to be a better way to do this. */
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    result.values[i * 4 + j] += this->values[i * 4 + k] * mat.values[k * 4 + j];
                }
            }
        }

        return result;
    }

    bool operator==(const Mat4 &mat) const
    {
        return this->values == mat.values;
    }

    // this is _not_ going to allow for the setting of values. To do that
    // I believe we would have to return a reference to the internal values
    // array.
    Vec4 operator[](int index) const
    {
        // I'm not sure if I should be checking the bounds here. Seems likely.
        return Vec4{
            this->values[index * 4],
            this->values[index * 4 + 1],
            this->values[index * 4 + 2],
            this->values[index * 4 + 3],
        };
    }

    void dump() const
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                std::cout << this->values[i * 4 + j] << std::setw(8);
            }
            std::cout << std::endl;
        }
    }
};

/* Generate a translation matrix for a given vector. */
Mat4 translation(Vec3 vec)
{
    std::array<float, 16> values = {
        1, 0, 0, vec[0],
        0, 1, 0, vec[1],
        0, 0, 1, vec[2],
        0, 0, 0, 1};

    return Mat4{values};
}

/* Generate a scaling matrix for a given vector. */
Mat4 scaling(Vec3 vec)
{
    std::array<float, 16> values = {
        vec[0], 0, 0, 0,
        0, vec[1], 0, 0,
        0, 0, vec[2], 0,
        0, 0, 0, 1};

    return Mat4{values};
}

Mat4 rotate_x_axis(float theta) {
    float theta_radians = theta * PI / 180;
    std::array<float, 16> values = {
        1, 0, 0, 0,
        0, cos(theta_radians), -sin(theta_radians), 0,
        0, sin(theta_radians), cos(theta_radians), 0,
        0, 0, 0, 1,
    };
    return Mat4{values};
}

Mat4 rotate_y_axis(float theta) {
    float theta_radians = theta * PI / 180;
    std::array<float, 16> values = {
        cos(theta_radians), 0, sin(theta_radians), 0,
        0, 1, 0, 0,
        -sin(theta_radians), 0, cos(theta_radians), 0,
        0, 0, 0, 1,
    };
    return Mat4{values};
}

Mat4 rotate_z_axis(float theta) {
    float theta_radians = theta * PI / 180;
    std::array<float, 16> values = {
        cos(theta_radians), -sin(theta), 0, 0,
        sin(theta_radians), cos(theta_radians), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
    };
    return Mat4{values};
}

Mat4 projection(float fov, float aspect_ratio, float znear, float zfar)
{
    float fov_radians = fov * PI / 180;
    float e = 1.0 / tan(fov_radians / 2.0f);
    // TODO: this formatting is really rough. Need to mess with
    // some settings.
    std::array<float, 16> values = {
        1 / aspect_ratio * (1 / tan(fov_radians / 2.0f)), 0, 0, 0,
        0, (1 / tan(fov_radians / 2.0f)), 0, 0,
        0, 0, (zfar + znear / (znear - zfar)), (2 * zfar * znear / (zfar - znear)),
        0, 0, -1, 0};

    return Mat4{values};
}

#endif // KUTARAGI_MATRIX_H
