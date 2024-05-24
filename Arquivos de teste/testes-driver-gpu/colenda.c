#include "address_map_arm.h" //atualizar diretorio
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

/*Sprite's offset*/
#define ORANGE_BLOCK 0
#define BLUE_BLOCK 1
#define MEDAL 2
#define BOMB 3
#define TREE 4
#define SHIP_UP 5
#define SHIP_RIGHT 6
#define SHIP_DOWN 7
#define SHIP_LEFT 8
#define COIN 9
#define DIAMOND 10
#define LASER_VERTICAL 11
#define LASER_DIAGONAL1 12
#define LASER_HORIZONTAL 13
#define LASER_DIAGONAL2 14
#define HEART 15
#define LOG 16
#define BLUE_CAR 17
#define GREEN_CAR 18
#define PURPLE_CAR 19
#define YELLOW_CAR 20
#define ALIEN1 21
#define ALIEN2 22
#define DRAGON 23
#define CUP 24

/*Opcodes */
#define WBR 0 //0000
#define WBM 2 //0010
#define DP 3 //0011

/* Sprite data*/
typedef struct Sprite
{
  int coord_x;
  int coord_y;
  int offset;
  int data_register;
  int visibility;
};

typedef struct Polygon
{
  int coord_x;
  int coord_y;
  int mem_address;
  int shape; //0 -> quadrado  1 -> triangulo
  int size;
  int red;
  int green;
  int blue;
};



/* Protótipos das funções*/
void open();
void set_background_color(int, int, int);
void set_block_background(int, int, int, int);
void set_sprite(Sprite *);  
void set_polygon(Polygon *);
void close();
