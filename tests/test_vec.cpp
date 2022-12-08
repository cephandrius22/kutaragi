#include <vec.h>
#include <assert.h>

void test_add() {
    Vec3 a {1,2,3};
    Vec3 b {1,2,3};
    Vec3 result = a + b;
    Vec3 expected{2,4,6};

    assert(expected == result);
}

void test_sub() {
    Vec3 a {1,2,3};
    Vec3 b {1,2,3};
    Vec3 result = a - b;
    Vec3 expected{0,0,0};

    assert(expected == result);
}

void test_mult_vec() {
    Vec3 a {1,2,3};
    Vec3 b {1,2,3};
    Vec3 result = a * b;
    Vec3 expected{1,4,9};

    assert(expected == result);
}

void test_mult_scalar() {
    Vec3 a {1,2,3};
    Vec3 result = a * 3;
    Vec3 expected{3,6,9};

    assert(expected == result);
}

void test_dot() {
    Vec3 a {1,2,3};
    Vec3 b {1,2,3};
    float result = dot(a, b);
    float expected = 14;

    assert(expected == result);
}

void test_vec4() {
    Vec3 a {1, 2, 3};
    Vec4 result {a, 1};
    Vec4 expected {1, 2, 3, 1};

    assert(expected == result);
}

int main(int argc, char *argv[]) {
    test_add();
    test_sub();
    test_mult_vec();
    test_mult_scalar();
    test_dot();
    test_vec4();

    return 0;
}