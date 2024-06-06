#include "colenda.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/stat.h>

int dev;

int instCount = 0;

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
  char instruction_binary_string[65] = {0}; //string que guarda a instrução a ser escrita no arquivo de comunicação com a GPU
  char binaryString[11] = {0};
  ssize_t bytes_written = 0;

  //validação dos valores inseridos pelo usuario
  if(color.red > 7 || color.green > 7 || color.blue > 7){
    perror("valor fora do limite de representação\n");
    return -1;
  } else if(color.red < 0 || color.green < 0 || color.blue < 0) {
    perror("valor fora do limite de representação\n");
    return -1;
  } 

  //conversão dos campos em string e concateção das strings na instrução
  int_to_binary_string(color.blue, binaryString, 3);
  strcat(instruction_binary_string, binaryString);
  int_to_binary_string(color.green, binaryString, 3);
  strcat(instruction_binary_string, binaryString);
  int_to_binary_string(color.red, binaryString, 3);
  strcat(instruction_binary_string, binaryString);
  int_to_binary_string(0,binaryString, 5);
  strcat(instruction_binary_string, binaryString);
  int_to_binary_string(WBR, binaryString, 4);
  strcat(instruction_binary_string, binaryString);

  //coloca o ponteiro de escrita no arquivo no começo do documento
  lseek(dev, 0, SEEK_SET);

  //escrita da instrução no arquivo de comunicação com a gpu
  write_in_gpu(instruction_binary_string);

  //caso ocorra algum erro retorna que não foi possivel alterar a cor do fundo
  if(bytes_written == -1) {
    perror("não foi possivel mudar a cor base do fundo\n");
    return -1;
  }
  return 0;
}

int set_block_background(BackGroundBlock bgBlock) {

  char instruction_binary_string[65] = {0}; //string que guarda a instrução a ser escrita no arquivo de comunicação com a GPU
  char binaryString[13] = {0}; // string responsavel por guardar o binario do numero convertido
  ssize_t bytes_written = 0;

  //verificação das informações vindas do usuario
  if(bgBlock.color.blue > 7 || bgBlock.color.green > 7 | bgBlock.color.red > 7 || bgBlock.mem_address > 4096){
    perror("valor fora do limite de representação\n");
    return -1;
  } else if(bgBlock.color.blue < 0 || bgBlock.color.green < 0 || bgBlock.color.red < 0 || bgBlock.mem_address < 0){
    perror("valor fora do limite de representação\n");
    return -1;
  }

  //conversão dos campos em string e concateção das strings na instrução
  int_to_binary_string(bgBlock.color.blue, binaryString, 3);
  strcat(instruction_binary_string, binaryString);
  int_to_binary_string(bgBlock.color.green, binaryString, 3);
  strcat(instruction_binary_string, binaryString);
  int_to_binary_string(bgBlock.color.red, binaryString, 3);
  strcat(instruction_binary_string, binaryString);
  int_to_binary_string(bgBlock.mem_address, binaryString, 12);
  strcat(instruction_binary_string, binaryString);
  int_to_binary_string(WBM, binaryString, 4);
  strcat(instruction_binary_string, binaryString);

  //coloca o ponteiro de escrita no arquivo no começo do documento
  lseek(dev, 0, SEEK_SET);

  //escrita da instrução no arquivo de comunicação com a gpu
  do{
    bytes_written = write(dev, instruction_binary_string, strlen(instruction_binary_string));
  }while(bytes_written == -1);

  //caso ocorra algum erro retorna que não foi possivel alterar a cor do fundo
  if(bytes_written == -1) {
    perror("não foi possivel alterar o bloco do fundo\n");
    return -1;
  }
  return 0;
}

int set_sprite(Sprite sprite) {
  char instruction_binary_string[65] = {0}; //string que guarda a instrução a ser escrita no arquivo de comunicação com a GPU
  char binaryString[11] = {0};// string responsavel por guardar o binario do numero convertido
  ssize_t bytes_written = 0;

  //verificação das informações vindas do usuario
  if (sprite.visibility > 1 || sprite.coord_x > 640 || sprite.coord_y > 480 || sprite.offset > 24 || sprite.data_register > 32) {
    perror("valor fora do limite de representação\n");
    return -1;
  } else if (sprite.visibility < 0 || sprite.coord_x < 0 || sprite.coord_y < 0 || sprite.offset < 0 || sprite.data_register < 1) {
    perror("valor fora do limite de representação\n");
    return -1;
  }

  //conversão dos campos em string e concateção das strings na instrução
  instruction_binary_string[0] = (sprite.visibility & 1) ? '1' : '0';
  int_to_binary_string(sprite.coord_x, binaryString, 10);
  strcat(instruction_binary_string, binaryString);
  int_to_binary_string(sprite.coord_y, binaryString, 10);
  strcat(instruction_binary_string, binaryString);
  int_to_binary_string(sprite.offset, binaryString, 9);
  strcat(instruction_binary_string, binaryString);
  int_to_binary_string(sprite.data_register, binaryString, 5);
  strcat(instruction_binary_string, binaryString);
  int_to_binary_string(WBR, binaryString, 4);
  strcat(instruction_binary_string, binaryString);

  //coloca o ponteiro de escrita no arquivo no começo do documento
  lseek(dev, 0, SEEK_SET);

  //escrita da instrução no arquivo de comunicação com a gpu
  write_in_gpu(instruction_binary_string);

  //caso ocorra algum erro retorna que não foi possivel alterar a cor do fundo
  if(bytes_written == -1) {
    perror("não foi possivel criar sprite\n");
    return -1;
  }

  return 0;
}

int set_polygon(Polygon polygon) {
  char instruction_binary_string[65] = {0}; //string que guarda a instrução a ser escrita no arquivo de comunicação com a GPU
  char binaryString[20] = {0}; // string responsavel por guardar o binario do numero convertido
  ssize_t bytes_written = 0;

  //verificação das informações vindas do usuario
  if (polygon.shape > 1 || polygon.color.blue > 7 || polygon.color.green > 7 || polygon.color.red > 7 || polygon.size > 15 | polygon.coord_y > 480 || polygon.coord_x > 512 || polygon.mem_address > 15) {
    perror("valor fora do alcance de representação\n");
    return -1;
  } else if (polygon.shape < 0 || polygon.color.blue < 0 || polygon.color.green < 0 || polygon.color.red < 0 || polygon.size < 0 | polygon.coord_y < 0 || polygon.coord_x < 0 || polygon.mem_address < 0) {
    perror("valor fora do alcance de representação\n");
    return -1;
  }

  //conversão dos campos em string e concateção das strings na instrução
  int_to_binary_string(polygon.shape, binaryString, 1);
  strcat(instruction_binary_string, binaryString);
  int_to_binary_string(polygon.color.blue, binaryString, 3);
  strcat(instruction_binary_string, binaryString);
  int_to_binary_string(polygon.color.green, binaryString, 3);
  strcat(instruction_binary_string, binaryString);
  int_to_binary_string(polygon.color.red, binaryString, 3);
  strcat(instruction_binary_string, binaryString);
  int_to_binary_string(polygon.size, binaryString, 4);
  strcat(instruction_binary_string, binaryString);
  int_to_binary_string(polygon.coord_y, binaryString, 9);
  strcat(instruction_binary_string, binaryString);
  int_to_binary_string(polygon.coord_x, binaryString, 9);
  strcat(instruction_binary_string, binaryString);
  int_to_binary_string(polygon.mem_address, binaryString, 4);
  strcat(instruction_binary_string, binaryString);
  int_to_binary_string(DP, binaryString, 4);
  strcat(instruction_binary_string, binaryString);

  //coloca o ponteiro de escrita no arquivo no começo do documento
  lseek(dev, 0, SEEK_SET);

  //escrita da instrução no arquivo de comunicação com a gpu
  write_in_gpu(instruction_binary_string);

  //caso ocorra algum erro retorna que não foi possivel alterar a cor do fundo
  if(bytes_written == -1) {
    perror("não foi possivel criar o polygno\n");
    return -1;
  }

  return 0;
}

int set_pixel(Pixel pixel) {
  char instruction_binary_string[65] = {0}; //string que guarda a instrução a ser escrita no arquivo de comunicação com a GPU
  char binaryString[20] = {0};// string responsavel por guardar o binario do numero convertido
  ssize_t bytes_written = 0;

  //verificação das informações vindas do usuario
  if(pixel.color.blue > 7 || pixel.color.green > 7  || pixel.color.red > 7 || pixel.mem_address > 6384){
    perror("valor fora do limite de representação\n");
    return -1;
  } else if (pixel.color.blue < 0 || pixel.color.green < 0  || pixel.color.red < 0 || pixel.mem_address < 0) {
    perror("valor fora do limite de representação\n");
    return -1;
  }

  //soma o endereco de memoria com 10000 pois esse eh o primeiro endereco livre na memoria de sprites
  pixel.mem_address += 10000;

  //conversão dos campos em string e concateção das strings na instrução
  int_to_binary_string(pixel.color.blue, binaryString, 3);
  strcat(instruction_binary_string, binaryString);
  int_to_binary_string(pixel.color.green, binaryString, 3);
  strcat(instruction_binary_string, binaryString);
  int_to_binary_string(pixel.color.red, binaryString, 3);
  strcat(instruction_binary_string, binaryString);
  int_to_binary_string(pixel.mem_address, binaryString, 14);
  strcat(instruction_binary_string, binaryString);
  int_to_binary_string(WSM, binaryString, 4);
  strcat(instruction_binary_string, binaryString);

  //coloca o ponteiro de escrita no arquivo no começo do documento
  lseek(dev, 0, SEEK_SET);

  //escrita da instrução no arquivo de comunicação com a gpu
  write_in_gpu(instruction_binary_string);

  //caso ocorra algum erro retorna que não foi possivel alterar a cor do fundo
  if(bytes_written == -1) {
    perror("não foi possivel criar o pixel\n");
    return -1;
  }
  return 0;
}

int clear() {
  int i;

  //Poligno desabilitado
  Polygon disablePolygon;
  disablePolygon.coord_x = 0;
  disablePolygon.coord_y = 0;
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
  for(i = 0; i < 4096; i++){
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

int int_to_binary(int number, int* binaryVector, int size){
  
  //inicia o vetor com 0's
  for (int i = 0; i < size; i++) {
        binaryVector[i] = 0;
  }

  int i = 0;

  //enquanto o numero for maior que 0 e não tiver utrapassado a quantidade de bits realiza a conversão para binario
  while(number > 0 && i < size) {
    binaryVector[i] = number % 2;
    number = number / 2;
    i++;
  }
  return 0;
}

int binary_to_string(int* binaryVector, char* binaryString, int size) {

  //enquanto não chegar no tamanho
  for (int i = 0; i < size; i++) {
    //verifica se o bit é um ou zero e coloca no vetor a respectiva representação em caractere
      binaryString[size - 1 - i] = (binaryVector[i] & 1) ? '1' : '0';
  }
  binaryString[size] = '\0'; // Termina a string com o caractere nulo
  return 0;
}

int int_to_binary_string(int number, char* binaryString, int size){
    int len = size; // Número de bits necessário

    //aloca dinamicamente memoria pro vetor binario
    int *binaryVector = (int*)malloc(len * sizeof(int));
    if (binaryVector == NULL) {
        perror("Erro ao alocar memória para binaryVector");
        return -1;
    }

    //realiza a conversão pra um vetor de binarios
    int_to_binary(number, binaryVector, len);

    //realiza a conversão do vetor de binarios pra string
    binary_to_string(binaryVector, binaryString, len);

    //limpa a memoria reservada para o vetor de binarios 
    free(binaryVector);
    return 0;
}

void write_in_gpu(char * instruction_binary_string){
  ssize_t bytes_written;

  if(instCount == 12) {
    printf("limite de instruções\n");
    usleep(7500);
    instCount = 0;
  }

  instCount++;
  bytes_written = write(dev, instruction_binary_string, strlen(instruction_binary_string));

  if(bytes_written == -1) {
    printf("erro na escrita\n");
  }

  while(bytes_written == -1){
    usleep(5000);
    printf("tentando de novo\n");
    bytes_written = write(dev, instruction_binary_string, strlen(instruction_binary_string));
  }
}

int GPU_close() {

  //caso haja algum erro ao encerrar a comunicação retorna -1
  if(close(dev) == -1) {
    perror("não foi possivel encerrar o arquivo\n");
    return -1;
  }
  return 0;
}