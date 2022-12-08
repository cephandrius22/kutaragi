//
// Created by jvwri on 12/8/2022.
//

#ifndef KUTARAGI_MATRIX_H
#define KUTARAGI_MATRIX_H

#include <vec.h>
#include <array>

class Mat4 {
public:
    std::array<float, 4*4> values;

    Mat4() = default;
    Mat4(std::array<float, 16> values) : values(values) {}

    Mat4 operator*(const Vec4& vec) {
        Mat4 result{};
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.values[i * 4 + j] = this->values[i * 4 + j] * vec[j];
            }
        }
    }
};

#endif //KUTARAGI_MATRIX_H
