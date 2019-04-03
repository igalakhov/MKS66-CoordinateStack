//
// Created by Ivan Galakhov on 2019-02-06.
//

#include "display.h"
#include <fstream>
#include <sstream>

void Display::clear(){
    unsigned char *cur = values;

    // fill in values
    for (int i = 0; i < NUM_PIXELS * 3; i++) {
        switch (i % 3) {
            case 0:
                *cur = DEFAULT_COLOR_R;
                break;
            case 1:
                *cur = DEFAULT_COLOR_G;
                break;
            case 2:
                *cur = DEFAULT_COLOR_B;
                break;
            default: // never gets run anyways
                break;
        }

        cur++;
    }
}

void Display::display(){
    FILE * f;

    f = popen("display", "w");

    fprintf(f, "P3\n%d %d\n%d\n", IMAGE_WIDTH, IMAGE_HEIGHT, MAX_COLOR);

    unsigned char * cur = values;

    for(int h = NUM_PIXELS * 3; h >= 0; h -= IMAGE_WIDTH * 3){
        for(int i = 0; i < IMAGE_WIDTH * 3; i++){
            fprintf(f, "%d ", (int) values[h + i]);
        }
    }

    for(int i = 0; i < NUM_PIXELS*3; i++, cur++)
        fprintf(f, "%d ", (int) * cur);

    pclose(f);

}

void Display::set(int x, int y, struct color * to_set){
    assert((y*IMAGE_WIDTH + x) < NUM_PIXELS);

    unsigned char * cur = values + ((y*IMAGE_WIDTH) + x)*3;

    // "efficiency"
    *cur = to_set->r;
    cur++;
    *cur = to_set->g;
    cur++;
    *cur = to_set->b;

}

// default saves as ppm
// change extention to save as
void Display::save(std::string file_name, std::string){

    // write values in display to file
    std::ofstream img_file;
    img_file.open(file_name, std::ofstream::trunc);

    img_file << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n" << MAX_COLOR << "\n";

    unsigned char *cur = values;

    for(int h = NUM_PIXELS * 3; h >= 0; h -= IMAGE_WIDTH * 3){
        for(int i = 0; i < IMAGE_WIDTH * 3; i++){
            img_file << std::to_string((int) values[h + i]) << " ";
        }
    }

    img_file.close();

}

// constructor
Display::Display() {
    values = new unsigned char[NUM_PIXELS * 3];

    unsigned char *cur = values;

    // fill in values
    for (int i = 0; i < NUM_PIXELS * 3; i++) {
        switch (i % 3) {
            case 0:
                *cur = DEFAULT_COLOR_R;
                break;
            case 1:
                *cur = DEFAULT_COLOR_G;
                break;
            case 2:
                *cur = DEFAULT_COLOR_B;
                break;
            default: // never gets run anyways
                break;
        }

        cur++;
    }
}

// deconstructor
Display::~Display() {
    delete values;
}
