#include "address_map_arm.h" //atualizar diretorio
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

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

typedef struct {
  int red;
  int green;
  int blue;
} Color;

/* Sprite data*/
typedef struct {
  int coord_x;
  int coord_y;
  int offset;
  int data_register;
  int visibility;
} Sprite;

typedef struct {
  int coord_x;
  int coord_y;
  int mem_address;
  int shape; //0 . quadrado  1 . triangulo
  int size;
  Color color;
} Polygon;


typedef struct {
  int mem_address;
  Color color;
} BackGroundBlock;


typedef struct {
  int mem_address; // vai de 0 ate 6384
  Color color;
} Pixel;

/* Protótipos das funções*/
int GPU_open();
int set_background_color(Color color);
int set_block_background(BackGroundBlock bgBlock);
int set_sprite(Sprite sprite);
int set_polygon(Polygon polygon);
int set_pixel(Pixel pixel);
int clear();
int intToBinary(int, int *, int);
int binaryToString(int*, char*, int );
int intToBinaryString(int, char*, int);
int GPU_close();


int GPU_open(){

  //abrir o arquivo com permissão de escrita e caso exista, sobreescreve o arquivo
  dev = open("/dev/colenda", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  if(dev == -1) {
    perror("Fail to open file");
    return -1;
  }
  return 0;
}

int set_background_color(Color color){
  char string[65] = {0};
  char retorno[11] = {0};
  ssize_t bytes_written;

  //validação dos valores inseridos pelo usuario
  if(color.red > 7 || color.green > 7 || color.blue > 7){
    perror("valor fora do limite de representação\n");
    return -1;
  } else if(color.red < 0 || color.green < 0 || color.blue < 0) {
    perror("valor fora do limite de representação\n");
    return -1;
  } 

  intToBinaryString(color.blue, retorno, 3);
  strcat(string, retorno);
  intToBinaryString(color.green, retorno, 3);
  strcat(string, retorno);
  intToBinaryString(color.red, retorno, 3);
  strcat(string, retorno);
  intToBinaryString(0,retorno, 5);
  strcat(string, retorno);
  intToBinaryString(WBR, retorno, 4);
  strcat(string, retorno);



  bytes_written = write(dev, string, strlen(string));

  if(bytes_written == -1) {
    perror("não foi possivel mudar a cor base do fundo\n");
    return -1;
  }
  return 0;
}

int set_block_background(BackGroundBlock bgBlock) {
  char string[65] = {0};
  char retorno[13] = {0};
  ssize_t bytes_written;

  if(bgBlock.color.blue > 7 || bgBlock.color.green > 7 | bgBlock.color.red > 7 || bgBlock.mem_address > 4096){
    perror("valor fora do limite de representação\n");
    return -1;
  } else if(bgBlock.color.blue < 0 || bgBlock.color.green < 0 || bgBlock.color.red < 0 || bgBlock.mem_address < 0){
    perror("valor fora do limite de representação\n");
    return -1;
  }

  intToBinaryString(bgBlock.color.blue, retorno, 3);
  strcat(string, retorno);
  intToBinaryString(bgBlock.color.green, retorno, 3);
  strcat(string, retorno);
  intToBinaryString(bgBlock.color.red, retorno, 3);
  strcat(string, retorno);
  intToBinaryString(bgBlock.mem_address, retorno, 12);
  strcat(string, retorno);
  intToBinaryString(WBM, retorno, 4);
  strcat(string, retorno);

  lseek(dev, 0, SEEK_SET);

  bytes_written = write(dev, string, strlen(string));

  if(bytes_written == -1) {
    perror("não foi possivel alterar o bloco do fundo\n");
    return -1;
  }
  return 0;
}

/*func para desenhar um sprite*/
int set_sprite(Sprite sprite) {
  char string[65] = {0};
  char retorno[11] = {0};
  ssize_t bytes_written;

  if (sprite.visibility > 1 || sprite.coord_x > 640 || sprite.coord_y > 480 || sprite.offset > 24 || sprite.data_register > 32) {
    perror("valor fora do limite de representação\n");
    return -1;
  } else if (sprite.visibility < 0 || sprite.coord_x < 0 || sprite.coord_y < 0 || sprite.offset < 0 || sprite.data_register < 1) {
    perror("valor fora do limite de representação\n");
    return -1;
  }
  string[0] = (sprite.visibility & 1) ? '1' : '0';
  intToBinaryString(sprite.coord_x, retorno, 10);
  strcat(string, retorno);
  intToBinaryString(sprite.coord_y, retorno, 10);
  strcat(string, retorno);
  intToBinaryString(sprite.offset, retorno, 9);
  strcat(string, retorno);
  intToBinaryString(sprite.data_register, retorno, 5);
  strcat(string, retorno);
  intToBinaryString(WBR, retorno, 4);
  strcat(string, retorno);
  
  printf("string: %s\n", string);

  lseek(dev, 0, SEEK_SET);

  bytes_written = write(dev, string, strlen(string));

  if(bytes_written == -1) {
    perror("não foi possivel criar sprite\n");
    return -1;
  }

  return 0;
}


/*func para desenhar um poligno*/
int set_polygon(Polygon polygon) {
  char string[65] = {0};
  char retorno[20] = {0}; 
  ssize_t bytes_written;

  if (polygon.shape > 1 || polygon.color.blue > 7 || polygon.color.green > 7 || polygon.color.red > 7 || polygon.size > 15 | polygon.coord_y > 480 || polygon.coord_x > 512 || polygon.mem_address > 15) {
    perror("valor fora do alcance de representação\n");
    return -1;
  } else if (polygon.shape < 0 || polygon.color.blue < 0 || polygon.color.green < 0 || polygon.color.red < 0 || polygon.size < 0 | polygon.coord_y < 0 || polygon.coord_x < 0 || polygon.mem_address < 0) {
    perror("valor fora do alcance de representação\n");
    return -1;
  }

  intToBinaryString(polygon.shape, retorno, 1);
  strcat(string, retorno);
  intToBinaryString(polygon.color.blue, retorno, 3);
  strcat(string, retorno);
  intToBinaryString(polygon.color.green, retorno, 3);
  strcat(string, retorno);
  intToBinaryString(polygon.color.red, retorno, 3);
  strcat(string, retorno);
  intToBinaryString(polygon.size, retorno, 4);
  strcat(string, retorno);
  intToBinaryString(polygon.coord_y, retorno, 9);
  strcat(string, retorno);
  intToBinaryString(polygon.coord_x, retorno, 9);
  strcat(string, retorno);
  intToBinaryString(polygon.mem_address, retorno, 4);
  strcat(string, retorno);
  intToBinaryString(DP, retorno, 4);
  strcat(string, retorno);

  lseek(dev, 0, SEEK_SET);

  bytes_written = write(dev, string, strlen(string));

  if(bytes_written == -1) {
    perror("não foi possivel criar o polygno\n");
    return -1;
  }

  return 0;
}

int set_pixel(Pixel pixel) {
  char string[65] = {0};
  char retorno[20] = {0};
  ssize_t bytes_written;


  if(pixel.color.blue > 7 || pixel.color.green > 7  || pixel.color.red > 7 || pixel.mem_address > 6384){
    perror("valor fora do limite de representação\n");
    return -1;
  } else if (pixel.color.blue < 0 || pixel.color.green < 0  || pixel.color.red < 0 || pixel.mem_address < 0) {
    perror("valor fora do limite de representação\n");
    return -1;
  }

  //soma o endereco de memoria com 10000 pois esse eh o primeiro endereco livre na memoria de sprites
  pixel.mem_address += 10000;

  intToBinaryString(pixel.color.blue, retorno, 3);
  strcat(string, retorno);
  intToBinaryString(pixel.color.green, retorno, 3);
  strcat(string, retorno);
  intToBinaryString(pixel.color.red, retorno, 3);
  strcat(string, retorno);
  intToBinaryString(pixel.mem_address, retorno, 14);
  strcat(string, retorno);
  intToBinaryString(WSM, retorno, 4);
  strcat(string, retorno);

  lseek(dev, 0, SEEK_SET);

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
    disablePolygon.mem_address = i;

    if(set_polygon(disablePolygon) == -1){
      perror("erro ao limpar memoria de polignos\n");
      break;
    }
  }

  
  Color bgBasicColor;
  bgBasicColor.red = 0;
  bgBasicColor.green = 0;
  bgBasicColor.blue = 0;

  if(set_background_color(bgBasicColor) == -1){
    perror("erro ao mudar a cor de fundo\n");
  }

  Sprite disableSprite;
  disableSprite.coord_x = 0;
  disableSprite.coord_y = 0;
  disableSprite.visibility = 0;
  disableSprite.offset = 0;

  for(i = 1; i < 32; i++){
    disableSprite.data_register = i;
    if(set_sprite(disableSprite) == -1){
      perror("erro ao desabilitar sprite\n");
      break;  
    }
  }

  return 0;

}

/* Função para converter um número em uma string binária */
int intToBinary(int number, int* binary_vector, int tamanho){
  int indice = 0;

  for (int i = 0; i < tamanho; i++) {
        binary_vector[i] = 0;
  }

  while(number > 0 && indice < tamanho) {
    binary_vector[indice] = number % 2;
    number = number / 2;
    indice++;
  }
  return 0;
}

int binaryToString(int* binaryVector, char* binaryString, int size) {
  for (int i = 0; i < size; i++) {
      binaryString[size - 1 - i] = (binaryVector[i] & 1) ? '1' : '0';
  }
  binaryString[size] = '\0'; // Termina a string com o caractere nulo
  return 0;
}

int intToBinaryString(int number, char* retorno, int size){
    int len = size; // Número de bits necessário

    int *binaryVector = (int*)malloc(len * sizeof(int));
    if (binaryVector == NULL) {
        perror("Erro ao alocar memória para binaryVector");
        return -1;
    }
    
    intToBinary(number, binaryVector, len);
    binaryToString(binaryVector, retorno, len);

    free(binaryVector);
    return 0;
}

int GPU_close() {

  if(close(dev) == -1) {
    perror("não foi possivel encerrar o arquivo\n");
    return -1;
  }
  return 0;
}