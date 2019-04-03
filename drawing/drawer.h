//
// Created by Ivan Galakhov on 2019-02-06.
//
#include "display.h"
#include "../matrix/edge_matrix.h"

#ifndef WORK_01_LINE_DRAWER_H
#define WORK_01_LINE_DRAWER_H

#include <cassert>
#include "display.h"
#include "../matrix/point_matrix.h"
#include "../matrix/edge_matrix.h"
#include "../matrix/triangle_matrix.h"
#include "../matrix/utils/vector_utils.h"

class Drawer : public Display {
public:
    Drawer(); // constructor

    // drawing basics
    void draw_points(PointMatrix *);
    void draw_edges(EdgeMatrix * );
    void draw_polygons(TriangleMatrix *);

    void draw_line(int, int, int, int);
    void draw_rectangle(int, int, int, int);
    void change_color(unsigned char, unsigned char, unsigned char);
    void set(int, int); // set a specific point to the current color

protected:

private:
    struct color cur_color; // current drawing color
};


#endif //WORK_01_LINE_DRAWER_H
