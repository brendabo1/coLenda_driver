#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "colenda.h"

int main() {
    GPU_open();
    clear();

    //cores
    Color black = {0, 0, 0};
    Color white = {7, 7, 7};
    Color softBlue = {2, 5, 7};
    Color red = {7, 0, 0};

    Polygon quadrado = {511,240,0,1,1,black};

    BackGroundBlock bg_block = {}


    

    GPU_close();

    return 0;
}
