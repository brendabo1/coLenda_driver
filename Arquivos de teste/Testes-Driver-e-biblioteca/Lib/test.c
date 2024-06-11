#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "colenda.c"

int main() {
    GPU_open();
    clear();

    //cores
    Color black = {0, 0, 0};
    Color white = {7, 7, 7};
    Color softBlue = {2, 5, 7};
    Color red = {7, 0, 0};
    Color red2 = {5, 0, 0};
    Color red3 = {4, 0, 0};
    Color gray = {2, 2, 2};
    Color gray2 = {4, 4, 4};

    
    set_background_color(white);
    draw_horizontal_block_line(21, 18, 6, red);
    draw_horizontal_block_line(21, 18, 7, red);
    draw_horizontal_block_line(21, 18, 8, red);

    draw_horizontal_block_line(21, 18, 9, black);
    draw_horizontal_block_line(21, 18, 10, black);
    draw_horizontal_block_line(21, 18, 11, black);

    draw_vertical_block_line(36, 15, 9, red);
    draw_vertical_block_line(36, 16, 9, red);
    draw_vertical_block_line(36, 17, 9, red);

    draw_vertical_block_line(36, 39, 9, red);
    draw_vertical_block_line(36, 40, 9, red);
    draw_vertical_block_line(36, 41, 9, red);

    draw_vertical_block_line(18, 18, 12, black);
    draw_vertical_block_line(18, 19, 12, black);
    draw_vertical_block_line(18, 20, 12, black);

    draw_vertical_block_line(18, 36, 12, black);
    draw_vertical_block_line(18, 37, 12, black);
    draw_vertical_block_line(18, 38, 12, black);

    draw_horizontal_block_line(21, 18, 27, black);
    draw_horizontal_block_line(21, 18, 28, black);
    draw_horizontal_block_line(21, 18, 29, black);

    draw_horizontal_block_line(21,18, 30, red);
    draw_horizontal_block_line(21,18, 31, red);
    draw_horizontal_block_line(21,18, 32, red);

    draw_horizontal_block_line(21, 18, 33, red);
    draw_horizontal_block_line(21, 18, 34, red);
    draw_horizontal_block_line(21, 18, 35, red);

    draw_horizontal_block_line(21, 18, 36, red);
    draw_horizontal_block_line(21, 18, 37, red);
    draw_horizontal_block_line(21, 18, 38, red);

    draw_horizontal_block_line(21, 18, 39, red);
    draw_horizontal_block_line(21, 18, 40, red);
    draw_horizontal_block_line(21, 18, 41, red);

    draw_horizontal_block_line(21, 18, 42, red);
    draw_horizontal_block_line(21, 18, 43, red);
    draw_horizontal_block_line(21, 18, 44, red);

    draw_horizontal_block_line(21, 18, 45, red);
    draw_horizontal_block_line(21, 18, 46, red);
    draw_horizontal_block_line(21, 18, 47, red);


    //desenho dos botões
    
    draw_horizontal_block_line(9, 18, 36, black);
    draw_horizontal_block_line(9, 18, 37, black);
    draw_horizontal_block_line(9, 18, 38, black);

    draw_vertical_block_line(9, 21, 33, black);
    draw_vertical_block_line(9, 22, 33, black);
    draw_vertical_block_line(9, 23, 33, black);

    draw_vertical_block_line(3, 30, 33, black);
    draw_vertical_block_line(3, 31, 33, black);
    draw_vertical_block_line(3, 32, 33, black);

    draw_vertical_block_line(3, 33, 36, black);
    draw_vertical_block_line(3, 34, 36, black);
    draw_vertical_block_line(3, 35, 36, black);
    
    





    

    GPU_close();
    return 0;
}
