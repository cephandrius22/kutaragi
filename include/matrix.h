#ifndef KUTARAGI_MATRIX_H
#define KUTARAGI_MATRIX_H

#include <vec.h>
#include <array>

class Mat4 {
public:
    // NOTE: these values are stored in row-major order
    std::array<float, 4*4> values{};

    Mat4() = default;
    Mat4(std::array<float, 16> values) : values(values) {}

    Vec4 operator*(const Vec4& vec) {
        Vec4 result{};
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.e[i] += this->values[i * 4 + j] * vec.e[j];
            }
        }

        return result;
    }

    Mat4 operator*(const Mat4& mat) {
        Mat4 result{};
        /* There has to be a better way to do this. */
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    result.values[i * 4 + j] += this->values[i * 4 + k] * mat.values[k * 4 + j];
                }
            }
        }

        return result;
    }

    bool operator==(const Mat4& mat) const {
        return this->values == mat.values;
    }
};

#endif //KUTARAGI_MATRIX_H
