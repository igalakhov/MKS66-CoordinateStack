//
// Created by Ivan Galakhov on 2019-02-06.
//

#include "drawer.h"

void Drawer::draw_points(PointMatrix * m){
    int n = m->size();
    float_mat * s = m->start();

    while(n > 0){
        set((int) s[0], (int) s[1], (int) s[2]);

        s += 4;

        n -= 1;
    }
}

// draw polygons
void Drawer::draw_polygons(TriangleMatrix * m){
    int n = m->size();
    float_mat * s = m->start();

    while(n > 0){

        bool draw = true;

        if(ENABLE_BACKFACE_CULLING){

            float_mat view[] = {0, 0, 1};

            float_mat A[] = {
                    s[4] - s[0],
                    s[5] - s[1],
                    s[6] - s[2]
            };

            float_mat B[] = {
                    s[8] - s[0],
                    s[9] - s[1],
                    s[10] - s[2]
            };

            float_mat * N = normalize(cross_product(A, B));


            if(dot_product(N, view) <= 0)
                draw = false;
        }

        if(draw) {

            // random colors because no lighting or z buffering

            cur_color.r = (unsigned char)(std::rand() % 255);
            cur_color.g = (unsigned char)(std::rand() % 255);
            cur_color.b = (unsigned char)(std::rand() % 255);

//            scan_line(s + 0, s + 4, s + 8);

            draw_line(s[0], s[1], s[2], s[4], s[5], s[6]);
            draw_line(s[4], s[5], s[6], s[8], s[9], s[10]);
            draw_line(s[0], s[1], s[2], s[8], s[9], s[10]);

        }

        s += 12;

        n -= 1;
    }
}

void Drawer::scan_line(float_mat * p0, float_mat * p1, float_mat * p2) {
    // swap so they're in the right oder

    if(p1[1] < p0[1])
        std::swap(p0, p1);

    if(p2[1] < p1[1])
        std::swap(p2, p1);

    if(p1[1] < p0[1])
        std::swap(p0, p1);

    if(p0[1] == p1[1] and p0[0] > p1[0])
        std::swap(p0, p1);

    if(p1[1] == p2[1] and p1[0] > p2[0])
        std::swap(p1, p2);

    float_mat y0 = p0[1];
    float_mat y1 = p1[1];
    float_mat y2 = p2[1];

    float_mat dy0 = y2 - y0;
    float_mat dy1 = y1 - y0;

    float_mat x0 = p0[0];
    float_mat x1 = x0;

    float_mat dx0 = (p2[0] - p0[0]) / dy0;
    float_mat dx1 = (p1[0] - p0[0]) / dy1;

    float_mat z0 = p0[2];
    float_mat z1 = z0;

    float_mat dz0 = (p2[2] - p0[2]) / dy0;
    float_mat dz1 = (p1[2] - p0[2]) / dy1;


    for(int y = int(y0); y < int(y1); y++){
        draw_line(int(x0), y, z0, int(x1), y, z1);

        x0 += dx0;
        x1 += dx1;

        z0 += dz0;
        z1 += dz1;
    }

    x1 = p1[0];

    dx0 = (p2[0] - p0[0])/(p2[1] - p0[1]);
    dx1 = (p2[0] - p1[0])/(p2[1] - p1[1]);

    z1 = p1[2];
    dz1 = (p2[2] - p1[2]) / (p2[1]-p1[1]);

    for(int y = int(y1); y < int(y2); y++){
        draw_line(int(x0), y, z0, int(x1), y, z1);

        x0 += dx0;
        x1 += dx1;

        z0 += dz0;
        z1 += dz1;
    }






}

// draw edges
void Drawer::draw_edges(EdgeMatrix * m){
    int max = m->size();
    float_mat * start = m->start();

    while(max > 0){
        draw_line((int) start[0], (int) start[1], start[2], (int) start[4], (int) start[5], start[6]);

        start += 8;

        max -= 1;
    }
}

void Drawer::draw_line(int x1, int y1, float_mat z1, int x2, int y2, float_mat z2) {
    // make sure x1 <= x2
    if (x1 > x2){
        draw_line(x2, y2, z1, x1, y1, z2);
        return;
    }

    // draws a line from (x1, x2) to (y1, y2)

    // get constants
    int dy = y2 - y1;
    int dx = x2 - x1;
    int a = dy;
    int b = -1*dx;

    //printf("dy: %d, dx: %d, a: %d, b: %d\n", dy, dx, a, b);

    // figure out the octet (amazing code right there)
    char octet = -1;
    if(dy == 0) octet = 1;
    else if(dx == 0)
        if(y2 > y1) octet = 2;
        else octet = 7;
    else if(dy > 0)
        if(dy > dx) octet = 2;
        else octet = 1;
    else
        if(abs(dy) > dx) octet = 7;
        else octet = 8;

    assert(octet != -1); // octet should be set

    // more values
    int x = x1;
    int y = y1;
    int d = 2*a + b;

    double z = z1;
    double dz = 0;

    // (260, 130)

    switch(octet){
        case 1:

            dz = ((double) z2 - z1)/(x2 - x1);

            while(x <= x2){
                set(x, y, z);
                if(d > 0){
                    y++;
                    d += 2*b;
                }
                x++;
                z += dz;
                d += 2*a;
            }
            break;
        case 2:

            dz = ((double) z2 - z1)/(y2 - y1);

            while(y <= y2){
                set(x, y, 0);
                if(d < 0){
                    x++;
                    d += 2*a;
                }
                y++;
                z += dz;
                d += 2*b;
            }
            break;
        case 8:

            dz = ((double) z2 - z1)/(x2 - x1);

            while(x <= x2){
                set(x, y, z);
                if(d < 0){
                    y--;
                    d -= 2*b;
                }
                x++;
                z += dz;
                d += 2*a;
            }
            break;
        case 7:

            dz = ((double) z2 - z1)/(y2 - y1);

            while(y >= y2){
                set(x, y, z);
                if(d > 0){
                    x++;
                    d += 2*a;
                }
                y--;
                z += dz;
                d -= 2*b;
            }
            break;
    }

}

void Drawer::set(int x, int y, float_mat z){
    if(x < IMAGE_WIDTH and x > 0 and y < IMAGE_HEIGHT and y > 0){ // only set if value is valid
        Display::set(x, y, z, &cur_color);
    }
}

void Drawer::change_color(unsigned char r, unsigned char g, unsigned char b){
    cur_color.r = r;
    cur_color.g = g;
    cur_color.b = b;
}

Drawer::Drawer() {
    cur_color.r = 0;
    cur_color.g = 255;
    cur_color.b = 102;

    z_buffer = new float_mat[NUM_PIXELS];
}

Drawer::~Drawer() {

    delete z_buffer;
}

