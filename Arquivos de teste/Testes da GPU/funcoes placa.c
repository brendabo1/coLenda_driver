#include "address_map_arm.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define DATAA 0x80
#define DATAB 0x70
#define WRFULL 0xb0
#define WRREG 0xc0





/*FUNCOES PARA GPU, A UNICA NAO UTILIZADA FOI A 0001*/
void setBgColor(volatile int * wrreg, volatile int * dataA, volatile int * dataB, int r, int g, int b); //0000
void setBgBlock(volatile int * wrreg, volatile int * dataA, volatile int * dataB, int endereco, int r, int g, int b); //0010
void setSprite(volatile int * wrreg, volatile int * dataA, volatile int * dataB, int registrador, int sprite, int cord_x, int cord_y, int sp); //0000   
void setPolygon(volatile int * wrreg, volatile int * dataA, volatile int * dataB, int endereco, int forma, int tamanho, int cord_x, int cord_y, int r, int g, int b); //0011



//muda a cor base do fundo
void setBgColor(volatile int * wrreg, volatile int * dataA, volatile int * dataB, int r, int g, int b) {
    *dataA = (0b00000 << 4) | 0b0000;
    *dataB = (b << 8) | (g << 3) | r;

    *wrreg = 1;
    *wrreg = 0;
}

void setBgBlock(volatile int * wrreg, volatile int * dataA, volatile int * dataB, int endereco, int r, int g, int b) {
    *dataA = (endereco << 4) | 0b0010;
    *dataB = (b << 8) | (g << 3) | r;

    *wrreg = 1;
    *wrreg = 0;
}

void setSprite(volatile int * wrreg, volatile int * dataA, volatile int * dataB, int registrador, int sprite, int cord_x, int cord_y, int sp){
    *dataA = (registrador << 4) | 0b0000;
    *dataB = (sp << 29) | (cord_x << 19) | (cord_y << 9) | sprite;

    *wrreg = 1;
    *wrreg = 0;
}

void setPolygon(volatile int * wrreg, volatile int * dataA, volatile int * dataB, int endereco, int forma, int tamanho, int cord_x, int cord_y, int r, int g, int b) {
    *dataA = (endereco << 4) | 0b0011;
    *dataB = (forma << 31) | (b << 28) | (g << 25) | (r << 22) | (tamanho << 18) | (cord_y << 9) | cord_x;

    *wrreg = 1;
    *wrreg = 0;
}


int main(){

    int fd = -1; // used to open /dev/mem
    void *LW_virtual; // physical addresses for light-weight bridge
    volatile int * dataA;
    volatile int * dataB;
    volatile int * wrreg;

    if ((fd = open( "/dev/mem", (O_RDWR | O_SYNC))) == -1) {
        printf ("ERROR: could not open \"/dev/mem\"...\n");
        return (-1);
    }

    // Get a mapping from physical addresses to virtual addresses
    LW_virtual = mmap (NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BRIDGE_BASE);
    if (LW_virtual == MAP_FAILED) {
        printf ("ERROR: mmap() failed...\n");
        close (fd);
        return (-1);
    }

    dataA = (int*) (LW_virtual + DATAA);
    dataB = (int*) (LW_virtual + DATAB);
    wrreg = (int*) (LW_virtual + WRREG);

    setPolygon(wrreg, dataA, dataB, 0b0000, 0, 0b0000, 320, 240, 0,0,7);


}