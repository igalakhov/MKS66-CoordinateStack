//
// Created by Ivan Galakhov on 2019-03-23.
//

#include "point_matrix.h"

PointMatrix::PointMatrix() : UnitMatrix(1) {}

void PointMatrix::add_point(float x0, float y0, float z0) {
    add_unit({x0, y0, z0});
}