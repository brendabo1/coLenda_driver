#include "colenda.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <wchar.h>

int dev;

int instCount = 0;

int GPU_open(){

  //abrir o arquivo com permissão de escrita e caso exista, sobreescreve o arquivo
  dev = open("/dev/colenda", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  if(dev == -1) {
    printf("Fail to open file");
    return -1;
  }
  return 0;
}

int set_background_color(Color color){
  char instruction2driver[8] = {0}; //string que guarda a instrução a ser escrita no arquivo de comunicação com a GPU
  wchar_t data2A = {0}, data2B = {0};


  //validação dos valores inseridos pelo usuario
  if((color.red > 7 || color.green > 7 || color.blue > 7) || (color.red < 0 || color.green < 0 || color.blue < 0)){
    printf("valor fora do limite de representação\n");
    return -1;
  } 

  data2A = (0b00000 << 4) | WBR;
  data2B = (color.blue << 6) | (color.green << 3) | color.red;

  wchar2string(data2A, data2B, instruction2driver);

  //coloca o ponteiro de escrita no arquivo no começo do documento
  lseek(dev, 0, SEEK_SET);

  //escrita da instrução no arquivo de comunicação com a gpu
  write_in_gpu(instruction2driver);

  return 0;
}

int set_block_background(BackGroundBlock bgBlock) {

  char instruction2driver[8] = {0}; //string que guarda a instrução a ser escrita no arquivo de comunicação com a GPU
  wchar_t data2A, data2B;


  //verificação das informações vindas do usuario
  if((bgBlock.color.blue > 7 || bgBlock.color.green > 7 | bgBlock.color.red > 7 || bgBlock.mem_address > 4800 || (bgBlock.color.blue < 0 || bgBlock.color.green < 0 || bgBlock.color.red < 0 || bgBlock.mem_address < 0))){
    printf("valor fora do limite de representação\n");
    return -1;
  }

  data2A = (bgBlock.mem_address << 4) | WBM;
  data2B = (bgBlock.color.blue << 6) | (bgBlock.color.green << 3) | bgBlock.color.red;
  wchar2string(data2A, data2B, instruction2driver);

  //coloca o ponteiro de escrita no arquivo no começo do documento
  lseek(dev, 0, SEEK_SET);

  write_in_gpu(instruction2driver);
  return 0;
}

int set_sprite(Sprite sprite) {
  char instruction2driver[8] = {0}; //string que guarda a instrução a ser escrita no arquivo de comunicação com a GPU
  wchar_t data2A, data2B;

  //verificação das informações vindas do usuario
  if ((sprite.visibility > 1 || sprite.coord_x > 640 || sprite.coord_y > 480 || sprite.offset > 24 || sprite.data_register > 32) || (sprite.visibility < 0 || sprite.coord_x < 0 || sprite.coord_y < 0 || sprite.offset < 0 || sprite.data_register < 1)) {
    printf("valor fora do limite de representação\n");
    return -1;
  }

  data2A = (sprite.data_register << 4) | WBR;
  data2B = (sprite.visibility << 29) | (sprite.coord_x << 19) | (sprite.coord_y << 9) | sprite.offset;
  wchar2string(data2A, data2B, instruction2driver);

  //coloca o ponteiro de escrita no arquivo no começo do documento
  lseek(dev, 0, SEEK_SET);

  //escrita da instrução no arquivo de comunicação com a gpu
  write_in_gpu(instruction2driver);

  return 0;
}

int set_polygon(Polygon polygon) {
  char instruction2driver[8] = {0};
  wchar_t data2A, data2B;


  //verificação das informações vindas do usuario
  if ((polygon.shape > 1 || polygon.color.blue > 7 || polygon.color.green > 7 || polygon.color.red > 7 || polygon.size > 15 | polygon.coord_y > 480 || polygon.coord_x > 512 || polygon.mem_address > 15) || (polygon.shape < 0 || polygon.color.blue < 0 || polygon.color.green < 0 || polygon.color.red < 0 || polygon.size < 0 | polygon.coord_y < 0 || polygon.coord_x < 0 || polygon.mem_address < 0)) {
    printf("valor fora do alcance de representação\n");
    return -1;
  } 



if((polygon.color.blue | polygon.color.green | polygon.color.red) & ~7){
  
}

  if (((polygon.shape+1)*10)/2 > polygon.coord_x || ((polygon.shape+1)*10)/2 > polygon.coord_y){
    printf("posição invalida para triangulos, por favor informar um numero maior ou igual a 45\n");
    return -1;
  }

  data2A =  (polygon.mem_address << 4) | DP;
  data2B = (polygon.shape << 31) | (polygon.color.blue << 28) | (polygon.color.green << 25) | (polygon.color.red << 22) | (polygon.size << 18) | (polygon.coord_y << 9) | polygon.coord_x;
  wchar2string(data2A, data2B, instruction2driver);

  //coloca o ponteiro de escrita no arquivo no começo do documento
  lseek(dev, 0, SEEK_SET);

  //escrita da instrução no arquivo de comunicação com a gpu
  write_in_gpu(instruction2driver);

  return 0;
}

int set_pixel(Pixel pixel) {
  char instruction2driver[8] = {0};
  wchar_t data2A, data2B;


  //verificação das informações vindas do usuario
  if((pixel.color.blue > 7 || pixel.color.green > 7  || pixel.color.red > 7 || pixel.mem_address > 6384) || (pixel.color.blue < 0 || pixel.color.green < 0  || pixel.color.red < 0 || pixel.mem_address < 0)){
    printf("valor fora do limite de representação\n");
    return -1;
  }

  //soma o endereco de memoria com 10000 pois esse eh o primeiro endereco livre na memoria de sprites
  pixel.mem_address += 10000;

  data2A = (pixel.mem_address << 4) | WSM;
  data2B = (pixel.color.blue << 6) | (pixel.color.green << 3) | (pixel.color.red);
  wchar2string(data2A, data2B, instruction2driver);

  //coloca o ponteiro de escrita no arquivo no começo do documento
  lseek(dev, 0, SEEK_SET);

  //escrita da instrução no arquivo de comunicação com a gpu
  write_in_gpu(instruction2driver);
  return 0;
}

int clear() {
  int i;

  //Poligno desabilitado
  Polygon disablePolygon;
  disablePolygon.coord_x = 320;
  disablePolygon.coord_y = 320;
  disablePolygon.size = 0;
  disablePolygon.shape = 0;
  disablePolygon.color.red = 0;
  disablePolygon.color.green = 0;
  disablePolygon.color.blue = 0;

  //passa por todos os endereços 
  for(i = 0; i < 16; i++){
    disablePolygon.mem_address = i;

    //escreve um poligno desabilitado
    set_polygon(disablePolygon);
  }

  //Cor preta
  Color bgBasicColor;
  bgBasicColor.red = 0;
  bgBasicColor.green = 0;
  bgBasicColor.blue = 0;

  //muda a cor do fundo para preto
  set_background_color(bgBasicColor);

  BackGroundBlock bgDisableBlock;
  bgDisableBlock.color.blue = 7;
  bgDisableBlock.color.green = 7;
  bgDisableBlock.color.red = 6;
  for(i = 0; i < 4800; i++){
    bgDisableBlock.mem_address = i;
    set_block_background(bgDisableBlock);
  }

  //criar um sprite desabilitado
  Sprite disableSprite;
  disableSprite.coord_x = 0;
  disableSprite.coord_y = 0;
  disableSprite.visibility = 0;
  disableSprite.offset = 0;

  //passa por todos os endereços de sprite
  for(i = 1; i < 32; i++){
    disableSprite.data_register = i;

    //insere um sprite desabilitado
    set_sprite(disableSprite);
  }

  return 0;

}

void wchar2string(wchar_t data2A, wchar_t data2B, char * retorno){
  for(int i = 0; i <4 ; i++){
    retorno[i] = (data2B >> (8 * (3 - i))) & 0xFF;
    retorno[i+4] = (data2A >> (8 * (3 - i))) & 0xFF;
  }
  //00000000000000000000000000000000
}

void write_in_gpu(char * instruction_binary_string){
  ssize_t bytes_written;

  if(instCount == 14) {
    usleep(7500);
    instCount = 0;
  }

  instCount++;
  bytes_written = write(dev, instruction_binary_string, 8);

  if(bytes_written == -1) {
    printf("erro na escrita\n");
  }

  while(bytes_written == -1){
    usleep(8000);
    printf("tentando de novo\n");
    bytes_written = write(dev, instruction_binary_string, 8);
  }
  //printf("%d", bytes_written);
}

int GPU_close() {

  //caso haja algum erro ao encerrar a comunicação retorna -1
  if(close(dev) == -1) {
    printf("não foi possivel encerrar o arquivo\n");
    return -1;
  }
  return 0;
}