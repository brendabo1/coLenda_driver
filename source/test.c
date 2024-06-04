#include <stdio.h>
#include <unistd.h>
#include "colenda.h"



int main() {

    struct timespec req = {0, 500000000};

    GPU_open();

    Sprite sp;
    sp.coord_x = 150;
    sp.coord_y = 460;
    sp.data_register = 2;
    sp.visibility = 1;
    sp.offset = PURPLE_CAR;

    Polygon pol;
    pol.color.red = 7;
    pol.color.blue = 7;
    pol.color.green = 7;
    pol.coord_x = 150;
    pol.mem_address = 2;
    pol.shape = 0;
    pol.size = 1;

    Color color;

    color.red = 2;
    color.blue = 7;
    color.green = 5;

    set_background_color(color);

    set_sprite(sp);

    while(1){
        nanosleep(&req, NULL);
        sp.coord_y -= 20;
        set_sprite(sp);
        if(sp.coord_y <=20){
            sp.coord_y = 480;
        }
    }

    GPU_close();
    return 0;
}
