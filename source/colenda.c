#include "address_map_arm.h" //atualizar diretorio
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#define WSM 1 //0001
#define WBM 2 //0010
#define DP 3 //0011


typedef struct Color
{
  int red;
  int green;
  int blue;
}

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
  struct Color color;
};


typedef struct BackGroundBlock
{
  int mem_adress;
  struct Color color;
};


typedef struct Pixel
{
  int mem_adress; // vai de 0 ate 6384
  struct Color color;
};

/* Protótipos das funções*/
void open();
void set_background_color(Color * color);
void set_block_background(BackGroundBlock * bgBlock);
void set_sprite(Sprite * sprite);
void set_polygon(Polygon * polygon);
void setPixel(Pixel * pixel);
void clear();
int  intToBinary(long long int, char*, int);
void close();


void open(){
  int dev = open("/dev/colenda", O_RDONLY)
  if(dev == -1) printf("Fail to open file");
  printf("Deu certo");
  close(dev);
}

void set_background_color(Color * color){
  long long int data = 0;
  char * string[65];

  data = ((color.blue << 15)|(color.green << 12)|(color.red <<9)|(0b0 << 4)|WBR);

  intToBinary(data, string, 65);

  //fazer parte de escrever no documento
}

void set_block_background(BackGroundBlock * bgBlock) {
  long long int data = 0;
  char * string[65];

  data = ((bgBlock.color.blue << 22) |( bgBlock.color.green << 19) | (bgBlock.color.red << 16) | (bgBlock.mem_adress << 4) | WSM);

  intToBinary(data, string, 65);

  //fazer parte de escrever no documento
}

/*func para desenhar um sprite*/
void set_sprite(Sprite * sprite) {
  long long int data = 0;
  char * string[65];

  data = ((sprite.visibility << 38)|(sprite.coord_x << 28)|(sprite.coord_y << 18)|(sprite.offset << 9)|(sprite.data_register << 4)|WBR);

  intToBinary(data, string, 65);

  //fazer a parte de escrever no documento

}


/*func para desenhar um poligno*/
void set_polygon(Polygon * polygon) {
  long long int data = 0;
  char * string[65];


  data = ((polygon.shape << 39) | (polygon.color.blue << 36) | (polygon.color.green << 33)| (polygon.color.red << 30)| (polygon.size << 26) | (polygon.coord_y << 17) | (polygon.coord_x << 8) | (polygon.mem_address << 4) | DP);

  intToBinary(data, string, 65);

  //fazer a parte de escrever no documento

}

void setPixel(Pixel * pixel) {
  long long int data = 0;
  char * string[65];

  //soma o endereco de memoria com 10000 pois esse eh o primeiro endereco livre na memoria de sprites
  data = ((pixel.color.blue << 24)|(pixel.color.green << 21)|(pixel.color.red << 18)|((pixel.mem_adress + 10000) << 4)|WSM);

  //fazer a parte de escrever no documento
}


/*func responsavel por limpar a tela e remover todos os elementos nela dispostos*/
void clear() {
  int i;

  Polygon disablePolygon;
  disablePolygon.coord_x = 0;
  disablePolygon.coord_y = 0;
  disablePolygon.size = 0;
  disablePolygon.shape = 0;
  disablePolygon.color.red = 0;
  disablePolygon.color.green = 0;
  disablePolygon.color.blue = 0;
  for(i = 0; i < 16; i++){
    disablePolygon.mem_adress = i;
    set_polygon(&disablePolygon);
  }

  
  Color bgBasicColor;
  bgBasicColor.red = 0;
  bgBasicColor.green = 0;
  bgBasicColor.blue = 0;

  set_background_color(&bgBasicColor);

  Sprite disableSprite;
  disableSprite.coord_x = 0;
  disableSprite.coord_y = 0;
  disableSprite.visibility = 0;
  disableSprite.offset = 0;

  for(i = 1; i < 32; i++){
    disableSprite.data_register = i;
    set_sprite(&disableSprite);
  }

  Pixel disablePixel;
  //decimal correspondente ao 111 111 110
  disablePixel.color.red = 6;
  disablePixel.color.green = 7;
  disablePixel.color.blue = 7;

  for(i = 0; i < 6385; i++){
    disablePixel.mem_adress = i;
    set_pixel(&disablePixel);
  }

  BackGroundBlock disableBgBlock;
  //decimal correspondente ao 111 111 110
  disableBgBlock.color.red = 6;
  disableBgBlock.color.green = 7;
  disableBgBlock.color.blue = 7;

  for(i = 0; i < 4096; i++){
    disableBgBlock.mem_adress = i;
    set_background_block(&disableBgBlock);
  }

}

/*func para converter um numero em uma string binaria*/
int intToBinary(long long int number, char * string, int size){
  int i = 0;
  string[size - 1] = '\0';
  for(i = size-2; i >=0; i--){
    string[i] = (n & 1) ? '1':'0';
    n = n >> 1;
  }

}
