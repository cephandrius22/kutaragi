//
// Created by jvwri on 12/8/2022.
//

#ifndef KUTARAGI_MATRIX_H
#define KUTARAGI_MATRIX_H

#include <array>

class Mat4 {
public:
    std::array<float, 4*4> values;

    Mat4(std::array<float, 16> values) : values(values) {}
};

#endif //KUTARAGI_MATRIX_H
