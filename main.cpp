#include <iostream>

#include "drawing/drawer.h"
#include "parsing/mdl/mdl_parser.h"
#include "matrix/transformation_matrix.h"
#include "matrix/point_matrix.h"
#include "drawing/3d/3d.h"
#include "parsing/obj_parser.h"
#include "parsing/mdl/coordinate_stack.h"

int main(){
    auto p = new MDLParser("../script.mdl");

    p->run_file();


}
