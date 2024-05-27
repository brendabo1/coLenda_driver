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


int dev;

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
int open();
int set_background_color(Color * color);
int set_block_background(BackGroundBlock * bgBlock);
int set_sprite(Sprite * sprite);
int set_polygon(Polygon * polygon);
int setPixel(Pixel * pixel);
int clear();
int  intToBinary(long long int, char*, int);
int close();


int open(){

  //abrir o arquivo com permissão de escrita e caso exista dobreescreve o arquivo
  dev = open("/dev/colenda", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  if(dev == -1) {
    perror("Fail to open file");
    return -1
  }
  return 0;
}

int set_background_color(Color * color){
  long long int data = 0;
  char * string[65];
  ssize_t bytes_written;

  //validação dos valores inseridos pelo usuario
  if(color.red > 7 || color.green > 7 || color.blue > 7){
    perror("valor fora do limite de representação\n");
    return -1;
  } else if(color.red < 0 || color.green < 0 || color.blue < 0) {
    perror("valor fora do limite de representação\n");
    return -1;
  } 

  data = ((color.blue << 15)|(color.green << 12)|(color.red <<9)|(0b0 << 4)|WBR);

  intToBinary(data, string, 65);

  bytes_written = write(dev, string, strlen(string));

  if(bytes_written == -1) {
    perror("não foi possivel mudar a cor base do fundo\n");
    return -1;
  }
  return 0;
}

int set_block_background(BackGroundBlock * bgBlock) {
  long long int data = 0;
  char * string[65];
  ssize_t bytes_written;

  if(bgBlock.color.blue > 7 || bgBlock.color.green > 7 | bgBlock.color.red > 7 || bgBlock.mem_adress > 4096){
    perror("valor fora do limite de representação\n");
    return -1;
  } else if(bgBlock.color.blue < 0 || bgBlock.color.green < 0 || bgBlock.color.red < 0 || bgBlock.mem_adress < 0){
    perror("valor fora do limite de representação\n");
    return -1;
  }

  data = ((bgBlock.color.blue << 22) |( bgBlock.color.green << 19) | (bgBlock.color.red << 16) | (bgBlock.mem_adress << 4) | WSM);

  intToBinary(data, string, 65);

  bytes_written = write(dev, string, strlen(string));

  if(bytes_written == -1) {
    perror("não foi possivel alterar o bloco do fundo\n");
    return -1;
  }
  return 0;
}

/*func para desenhar um sprite*/
int set_sprite(Sprite * sprite) {
  long long int data = 0;
  char * string[65];
  ssize_t bytes_written;

  if (sprite.visibility > 1 || sprite.coord_x > 640 || sprite.coord_y > 480 || sprite.offset > 24 || sprite.data_register > 32) {
    perror("valor fora do limite de representação\n");
    return -1;
  } else if (sprite.visibility < 0 || sprite.coord_x < 0 || sprite.coord_y < 0 || sprite.offset < 0 || sprite.data_register < 1) {
    perror("valor fora do limite de representação\n");
    return -1;
  }

  data = ((sprite.visibility << 38)|(sprite.coord_x << 28)|(sprite.coord_y << 18)|(sprite.offset << 9)|(sprite.data_register << 4)|WBR);

  intToBinary(data, string, 65);

  bytes_written = write(dev, string, strlen(string));

  if(bytes_written == -1) {
    perror("não foi possivel criar sprite\n");
    return -1;
  }

  return 0;
}


/*func para desenhar um poligno*/
int set_polygon(Polygon * polygon) {
  long long int data = 0;
  char * string[65];
  ssize_t bytes_written;

  if (polygon.shape > 1 || polygon.color.blue > 7 || polygon.color.green > 7 || polygon.color.red > 7 || polygon.size > 15 | polygon.coord_y > 480 || polygon.coord_x > 640 || polygon.mem_address > 15) {
    perror("valor fora do alcance de representação\n");
    return -1;
  } else if (polygon.shape < 0 || polygon.color.blue < 0 || polygon.color.green < 0 || polygon.color.red < 0 || polygon.size < 0 | polygon.coord_y < 0 || polygon.coord_x < 0 || polygon.mem_address < 0) {
    perror("valor fora do alcance de representação\n");
    return -1;
  }


  data = ((polygon.shape << 39) | (polygon.color.blue << 36) | (polygon.color.green << 33)| (polygon.color.red << 30)| (polygon.size << 26) | (polygon.coord_y << 17) | (polygon.coord_x << 8) | (polygon.mem_address << 4) | DP);

  intToBinary(data, string, 65);

  bytes_written = write(dev, string, strlen(string));

  if(bytes_written == -1) {
    perror("não foi possivel criar o polygno\n");
    return -1;
  }

  return 0;
}

int setPixel(Pixel * pixel) {
  long long int data = 0;
  char * string[65];
  ssize_t bytes_written;


  if(pixel.color.blue > 7 || pixel.color.green > 7  || pixel.color.red > 7 || pixel.mem_adress > 6384){
    perror("valor fora do limite de representação\n");
    return -1;
  } else if (pixel.color.blue < 0 || pixel.color.green < 0  || pixel.color.red < 0 || pixel.mem_adress < 0) {
    perror("valor fora do limite de representação\n");
    return -1;
  }

  //soma o endereco de memoria com 10000 pois esse eh o primeiro endereco livre na memoria de sprites
  data = ((pixel.color.blue << 24)|(pixel.color.green << 21)|(pixel.color.red << 18)|((pixel.mem_adress + 10000) << 4)|WSM);

  bytes_written = write(dev, string, strlen(string));

  if(bytes_written == -1) {
    perror("não foi possivel criar o pixel\n");
    return -1;
  }
  return 0;
}


/*func responsavel por limpar a tela e remover todos os elementos nela dispostos*/
int clear() {
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

    if(set_polygon(&disablePolygon) == -1){
      perror("erro ao limpar memoria de polignos\n");
      break;
    }
  }

  
  Color bgBasicColor;
  bgBasicColor.red = 0;
  bgBasicColor.green = 0;
  bgBasicColor.blue = 0;

  if(set_background_color(&bgBasicColor) == -1){
    perror("erro ao mudar a cor de fundo\n");
  }

  Sprite disableSprite;
  disableSprite.coord_x = 0;
  disableSprite.coord_y = 0;
  disableSprite.visibility = 0;
  disableSprite.offset = 0;

  for(i = 1; i < 32; i++){
    disableSprite.data_register = i;
    if(set_sprite(&disableSprite) == -1){
      perror("erro ao desabilitar sprite\n");
      break;  
    }
  }

  Pixel disablePixel;
  //decimal correspondente ao 111 111 110
  disablePixel.color.red = 6;
  disablePixel.color.green = 7;
  disablePixel.color.blue = 7;

  for(i = 0; i < 6385; i++){
    disablePixel.mem_adress = i;
    if(set_pixel(&disablePixel) == -1){
      perror("erro ao desabilitar pixel\n");
      break;
    }
  }

  BackGroundBlock disableBgBlock;
  //decimal correspondente ao 111 111 110
  disableBgBlock.color.red = 6;
  disableBgBlock.color.green = 7;
  disableBgBlock.color.blue = 7;

  for(i = 0; i < 4096; i++){
    disableBgBlock.mem_adress = i;

    if(set_background_block(&disableBgBlock) == -1){
      perror("erro ao desabilitar bloco de background\n");
      break;
    }
  }

  return 0;

}

/*func para converter um numero em uma string binaria*/
int intToBinary(long long int number, char * string, int size){
  int i = 0;
  string[size - 1] = '\0';
  for(i = size-2; i >=0; i--){
    string[i] = (n & 1) ? '1':'0';
    n = n >> 1;
  }

  return 0;

}

int close() {

  if(close(dev) == -1) {
    perror("não foi possivel encerrar o arquivo\n");
    return -1;
  }
  return 0;
}