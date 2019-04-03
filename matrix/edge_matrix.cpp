//
// Created by Ivan Galakhov on 2019-02-19.
//

#include "edge_matrix.h"

EdgeMatrix::EdgeMatrix() : UnitMatrix(2) {}

void EdgeMatrix::add_edge(float x1, float y1, float z1, float x2, float y2, float z2) {
    add_unit({x1, y1, z1, x2, y2, z2});
}