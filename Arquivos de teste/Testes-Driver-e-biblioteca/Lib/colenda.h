#ifndef COLENDA_LIBRARY
#define COLENDA_LIBRARY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <wchar.h>
#include <stdint.h>

/*offset de cada sprite*/
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

/*Codigo das operações */
#define WBR 0 //0000
#define WSM 1 //0001
#define WBM 2 //0010
#define DP 3 //0011

/*Estrutura das cores*/
typedef struct {
    uint64_t red; // valor da intensidade da cor vermelha: vai de 0 a 7
    uint64_t green; //valor da intensidade da cor verde: vai de 0 a 7
    uint64_t blue; // valor da intensidade da cor azul: vai de 0 a 7
} Color;

/*Estrutura dos sprites*/
typedef struct {
    uint64_t coord_x; //coordenada do eixo x do centro do sprite: vai de 0 a 640
    uint64_t coord_y; //coordenada do eixo y do centro do sprite: vai de 0 a 480
    uint64_t offset; // identificação do sprite: vai de 0 a 24
    uint64_t data_register; //localização do sprite na memoria: vai de 1 a 31
    uint64_t visibility; // visibilidade do sprite: 0. invisivel  1. visivel
} Sprite;

/*Estrutura dos polignos*/
typedef struct {
    uint64_t coord_x; // coordenada referente ao eixo x do centro do poligno: vai de 0 a 511
    uint64_t coord_y; // coordenada referente ao eixo y do centro do poligno: vai de 0 a 480
    uint64_t mem_address; // numero referente a sobreposição: vai de 0 a 15
    uint64_t shape; //forma do poligno: 0 . quadrado  1 . triangulo
    uint64_t size; // tamanho do poligno: vai de 0 a 15
    Color color; 
} Polygon;

/*Estrura dos blocos do background*/
typedef struct {
    uint64_t mem_address; // endereço do bloco vai de 0 a 4096
    Color color; // cor referenteao bloco
} BackGroundBlock;

/*estrutura dos pixels*/
typedef struct {
  uint64_t mem_address; // endereço do pixel, vai de 0 a 6384
  Color color; //cor do pixel
} Pixel;

/**Função responsavel por inicializar a comunicação com a gpu
 * retorno: Retorna 0 caso  a inicialização seja bem sucedida e -1 caso contrario
*/
int GPU_open();

/**Função responsavel por definir a cor do fundo da tela
 * parametros: color -> Struct Color responsavel por organizar os dados de uma cor
 * retorno: Retorna 0 caso seja bem sucedido e -1 caso ocorra algum erro
*/
int set_background_color(Color color);

/**Função responsavel por alterar blocos do fundo da tela
 * paramentros: bgBlock -> Struct BackGroundBlock responsavel por organizar os dados referentes a um bloco
 * retorno: Retorna 0 caso seja bem sucedido e -1 caso ocorra algum erro
*/
int set_block_background(BackGroundBlock bgBlock);

/**Função responsavel por desenhar um sprite na tela
 * paramentros: sprite -> Struct Sprite responsavel por organizar os dados referentes a um sprite
 * retorno: Retorna 0 caso seja bem sucedido e -1 caso ocorra algum erro
*/
int set_sprite(Sprite sprite);

/**Função responsavel por desenhar um poligno (quadrado ou triangulo) na tela
 * paramentros: polygon -> Struct Polygon responsavel por organizar os dados referentes a um poligno
 * retorno: Retorna 0 caso seja bem sucedido e -1 caso ocorra algum erro
*/
int set_polygon(Polygon polygon);

/**Função responsavel por salvar um pixel na memória de sprites
 * paramentros: pixele -> Struct Pixel responsavel por organizar os dados referentes pixel na memoria de sprites
 * retorno: Retorna 0 caso seja bem sucedido e -1 caso ocorra algum erro
*/
int set_pixel(Pixel pixel);

/**Função responsavel por limpar a tela, muda a cor de fundo para preto, remove todos os sprites e pixels
 * retorno: Retorna 0 caso seja bem sucedido e -1 caso ocorra algum erro
*/
int clear();

/**Função responsavel por converter um inteiro pra um vetor de 1's e 0's
 * parametros: number -> inteiro que deseja ser convertido em binario
 *             binaryVector -> vetor de inteiro que vai armazenar os binarios referentes ao numero convertido
 *             size -> inteito referente ao tamanho da quantidade de bits necessarios para representar o numero
*/
void wchar2string(wchar_t data2A, wchar_t data2B, char * retorno);

void write_in_gpu(char * instruction_binary_string);
/**Função responsavel por encerrar a comunicação com a GPU
 * retorno: Retorna 0 se bem sucedido e -1 caso contrario
*/

int GPU_close();


#endif