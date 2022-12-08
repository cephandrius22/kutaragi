#include <matrix.h>
#include <assert.h>
#include <iostream>

void test_vec_mult() {
    std::array<float, 16> values = {
            1, 2, 3, 4,
            3, 4, 5, 6,
            5, 6, 7, 8,
            7, 8, 9, 10
    };
    Mat4 mat{values};

    Vec4 vec{1, 2, 3, 4};

    Vec4 actual = mat * vec;
    Vec4 expected{30, 50, 70, 90};

    assert(expected == actual);
}


void test_mat_mult() {
    std::array<float, 16> values = {
            1, 2, 3, 4,
            3, 4, 5, 6,
            5, 6, 7, 8,
            7, 8, 9, 10
    };
    Mat4 a{values};
    Mat4 b{values};

    Mat4 actual = a * b;

    std::array<float, 16> expected_values = {
            50, 60, 70, 80,
            82, 100, 118, 136,
            114, 140, 166, 192,
            146, 180, 214, 248
    };
    Mat4 expected{expected_values};

    assert(expected == actual);
}

int main(int argc, char *argv[]) {
    test_vec_mult();
    test_mat_mult();
}