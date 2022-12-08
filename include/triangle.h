//
// Created by jvwri on 12/7/2022.
//

#ifndef KUTARAGI_TRIANGLE_H
#define KUTARAGI_TRIANGLE_H

#include <vec.h>

class Triangle {
public:
    Point3 a, b, c;

    // not clear on the difference between this and `Triangle() {}`
    Triangle() = default;

    Triangle(Point3 a, Point3 b, Point3 c) : a(a), b(b), c(c) {}
};

#endif //KUTARAGI_TRIANGLE_H
