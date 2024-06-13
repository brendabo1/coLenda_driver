#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "colenda.h"

int main() {
    GPU_open();
    clear();

    //cores
    Color black = {0, 0, 0};
    Color darkBlue = {0, 0, 3};
    Color softBlue = {0, 0, 5};
    Color white = {7,7,7};
    Color red = {7, 0, 0};
    Color yellow = {7, 7, 0};

    
    set_background_color(white);
    draw_horizontal_block_line(60, 10, 6, red);
    draw_horizontal_block_line(60, 10, 7, red);
    draw_horizontal_block_line(60, 10, 8, red);

    draw_horizontal_block_line(60, 10, 9, black);
    draw_horizontal_block_line(60, 10, 10, black);
    draw_horizontal_block_line(60, 10, 11, black);



    draw_vertical_block_line(51, 7, 9, red);
    draw_vertical_block_line(51, 8, 9, red);
    draw_vertical_block_line(51, 9, 9, red);

    draw_vertical_block_line(51, 70, 9, red);
    draw_vertical_block_line(51, 71, 9, red);
    draw_vertical_block_line(51, 72, 9, red);

    //borda interna
    draw_vertical_block_line(33, 10, 12, black);
    draw_vertical_block_line(33, 11, 12, black);
    draw_vertical_block_line(33, 12, 12, black);

    draw_vertical_block_line(33, 67, 12, black);
    draw_vertical_block_line(33, 68, 12, black);
    draw_vertical_block_line(33, 69, 12, black);

    draw_horizontal_block_line(60, 10, 42, black);
    draw_horizontal_block_line(60, 10, 43, black);
    draw_horizontal_block_line(60, 10, 44, black);

    draw_horizontal_block_line(60, 10, 45, red);
    draw_horizontal_block_line(60, 10, 46, red);
    draw_horizontal_block_line(60, 10, 47, red);
    draw_horizontal_block_line(60, 10, 48, red);
    draw_horizontal_block_line(60, 10, 49, red);
    draw_horizontal_block_line(60, 10, 50, red);
    draw_horizontal_block_line(60, 10, 51, red);
    draw_horizontal_block_line(60, 10, 52, red);
    draw_horizontal_block_line(60, 10, 53, red);
    draw_horizontal_block_line(60, 10, 54, red);
    draw_horizontal_block_line(60, 10, 55, red);
    draw_horizontal_block_line(60, 10, 56, red);
    draw_horizontal_block_line(60, 10, 57, red);
    draw_horizontal_block_line(60, 10, 58, red);
    draw_horizontal_block_line(60, 10, 59, red);


    //desenha a tela interna
    for(int i = 12; i<42; i++){
        draw_horizontal_block_line(54, 13, i, darkBlue);
    }
    

    //desenho dos botões

    Polygon btn_quadrado;
    Polygon btn_triangulo;

    btn_quadrado.color = black;
    btn_triangulo.color = black;

    btn_quadrado.mem_address = 0;
    btn_triangulo.mem_address = 1;

    btn_quadrado.coord_x = 405;
    btn_quadrado.coord_y = 480;

    btn_triangulo.coord_x = 475;
    btn_triangulo.coord_y = 418;

    btn_triangulo.shape = 1;
    btn_quadrado.shape = 0;
    btn_quadrado.size = 5;
    btn_triangulo.size = 5;
    
    set_polygon(btn_quadrado);
    set_polygon(btn_triangulo);


    draw_vertical_block_line(4, 18, 53, black);
    draw_vertical_block_line(4, 19, 53, black);
    draw_vertical_block_line(4, 20, 53, black);
    draw_vertical_block_line(4, 21, 53, black);
    draw_vertical_block_line(4, 22, 53, black);
    draw_vertical_block_line(4, 23, 53, black);


    draw_horizontal_block_line(16, 13, 57, black);
    draw_horizontal_block_line(16, 13, 58, black);
    draw_horizontal_block_line(16, 13, 59, black);

    Sprite alien1 = {218, 126, ALIEN1, 1, 1};
    Sprite alien2 = {238, 146, ALIEN2, 2, 1};
    Sprite alien3 = {258, 166, ALIEN1, 3, 1};
    Sprite alien4 = {278, 186, ALIEN2, 4, 1};
    Sprite alien5 = {298, 186, ALIEN1, 5, 1};
    Sprite alien6 = {318, 166, ALIEN2, 6, 1};
    Sprite alien7 = {338, 146, ALIEN1, 7, 1};
    Sprite alien8 = {358, 126, ALIEN2, 8, 1};
    Sprite nave = {318, 300, SHIP_UP, 9, 1};
    Sprite vida1 = {440, 106, HEART, 10, 1};
    Sprite vida2 = {470, 106, HEART, 11, 1};
    Sprite vida3 = {500, 106, HEART, 12, 1};
    Sprite laser1 = {258, 256, LASER_VERTICAL, 13, 1};
    Sprite laser2 = {358, 244, LASER_VERTICAL, 14, 1};
    Sprite laser3 = {318, 280, LASER_VERTICAL, 15, 1};
    Sprite laser4 = {218, 186, LASER_VERTICAL, 16, 1};

    set_sprite(alien1);
    set_sprite(alien2);
    set_sprite(alien3);
    set_sprite(alien4);
    set_sprite(alien5);
    set_sprite(alien6);
    set_sprite(alien7);
    set_sprite(alien8);
    set_sprite(nave);
    set_sprite(vida1);
    set_sprite(vida2);
    set_sprite(vida3);
    set_sprite(laser1);
    set_sprite(laser2);
    set_sprite(laser3);
    set_sprite(laser4);

    GPU_close();
    return 0;
}
