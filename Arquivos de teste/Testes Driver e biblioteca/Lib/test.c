#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "colenda.c"
#include "colenda.h"



int main() {

    clock_t start, end;
    double cpu_used_time;

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
    pol.coord_x = 511;
    pol.coord_y = 480;
    pol.mem_address = 0;
    pol.shape = 1;
    pol.size = 0;

    Color color;

    color.red = 2;
    color.blue = 7;
    color.green = 5;

    clear();

    set_background_color(color);
    set_sprite(sp);

    printf("inicio da execição\n");
    start =  clock();
    set_polygon(pol);
    for(int i = 0; i<15; i++) {
        pol.mem_address++;
        set_polygon(pol);
    }
    end = clock();

    cpu_used_time = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("fim\ntempo de execução: %f\n", cpu_used_time);

    
    while(1){
        usleep(50000);
        sp.coord_y -= 20;
        set_sprite(sp);
        if(sp.coord_y <=20){
            sp.coord_y = 480;
        }
    }

    GPU_close();
    return 0;
}
