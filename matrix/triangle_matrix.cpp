//
// Created by Ivan Galakhov on 2019-03-23.
//

#include "triangle_matrix.h"

TriangleMatrix::TriangleMatrix() : UnitMatrix(3) {}

void TriangleMatrix::add_triangle(float x0, float y0, float z0,
                                  float x1 , float y1, float z1,
                                  float x2, float y2, float z2) {
    add_unit({x0, y0, z0, x1, y1, z1, x2, y2, z2});
}

