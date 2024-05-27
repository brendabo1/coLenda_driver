#include <stdio.h>
#include <unistd.h>
#include "colenda.c"



int main() {

    GPU_open();

    Sprite sp;
    sp.coord_x = 100;
    sp.coord_y = 100;
    sp.data_register = 2;
    sp.visibility = 1;
    sp.offset = BLUE_BLOCK;

    Polygon pol;
    pol.color.red = 7;
    pol.color.blue = 7;
    pol.color.green = 7;
    pol.coord_x = 300;
    pol.coord_y = 200;
    pol.mem_address = 2;
    pol.shape = 0;
    pol.size = 1;

    Color color;

    color.red = 7;
    color.blue = 0;
    color.green = 0;

    set_sprite(sp);

    GPU_close();
    return 0;
}

// 1'111'111'111'0001'011001000'100101100'0010'0011