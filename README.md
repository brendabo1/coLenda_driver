<h1 align="center"><i>Driver CoLenda</i></h1>

<h3 align="center">Comunicação com o dispositivo gráfico CoLenda</h3>

<p align="center">O Driver CoLenda é um driver de caractere simples e eficiente que realiza a comunicação entre o processador de
	propósito geral e o hardware. A biblioteca inclusa abstrai a comunicação entre aplicações de usuário e o driver.</p>

<h4 align="center">
<a href="https://github.com/camilaqPereira/coLenda_driver/commits/main/"> <img alt="coLenda_driver commits" 
										  src="https://img.shields.io/github/last-commit/camilaqPereira/coLenda_driver/main"></a>
<a href="https://github.com/camilaqPereira/coLenda_driver/pulls"> <img alt="coLenda_driver Pull Requests" 
										  src="https://img.shields.io/github/issues-pr/camilaqPereira/coLenda_driver">
</a>
<a href="https://github.com/camilaqPereira/coLenda_driver"><img alt="coLenda_driver repo" 
								   src="https://img.shields.io/github/created-at/camilaqPereira/coLenda_driver">
</a>
</h4>

<div align="center">
	
[Sobre o projeto](README.md#sobre-o-projeto) • [Instalação](README.md#instalação) • [Solução geral](README.md#solução-geral) • [Driver](README.md#driver-colenda-1) •
[Biblioteca](README.md#biblioteca-colenda) • [Testes](README.md#produto-e-testes-realizados)

</div>

## Sobre o projeto

A Unidade de Processamento Gráfico (GPU) é um microprocessador especializado e paralelo dedicado à aceleração de computações gráficas. Este processador foi desenvolvido especificamente 
para a realização de diversas operações com valores de ponto flutuante, essenciais para o processamento de gráficos 2D/3D. Atualmente, as GPUs, além de serem potentes dispositivos 
gráficos, são processadores paralelos altamente programáveis que apresentam alta precisão e poderosos recursos.

Neste contexto de grande evolução das unidades de processamento gráfico e de crescente popularidade dessas, o presente projeto implementa um de um módulo kernel para o processador 
gráfico CoLenda na HPS do kit de desenvolvimento DE1-SoC. Além disso, implementa também uma biblioteca para facilitar a utilização do driver.

<details>
<summary> <h3>Requisitos</h3></summary>
	
A presente projeto deve atender às condições e aos requisitos predeterminados, de modo que:
- a placa De1-SoC seja utilizada para o desenvolvimento do projeto
- todos os códigos deve ser escritos na linguagem C e devem ser detalhadamente comentados;
- sejam desenvolvidos módulos de kernel Linux para o processador gráfico CoLenda;
- seja desenvolvida uma biblioteca para facilitar a utilização do processador;
- a biblioteca deve conter, no mínimo, uma função para cada instrução do processador gráfico e deve seguir as recomendações descritas em [C coding style por Tilen Majerle](https://github.com/MaJerle/c-code-style);
- seja desenvolvido um código que ilustre a utilização de todos os elementos disponibilizados pela pelo processador gráfico e um script do tipo *Makefile* para a geração do executável;
- a descrição técnica do projeto seja realizada no README do proketo;
- seja realizada a descrição dos testes de funcionamento, bem como dos resultados alcançados.

A descrição do projeto está disponível [aqui](/docs/Descricao-do-problema.pdf)
</details>

## Contribuidores

<a href="https://github.com/brendabo1"><img src="https://avatars.githubusercontent.com/u/69097241?v=4" title="brendabo1" width="50" height="50"></a>
<a href="https://github.com/camilaqPereira"><img src="https://avatars.githubusercontent.com/u/116687830?v=4" title="camilaqPereira" width="50" height="50"></a>
<a href="https://github.com/DestinyWolf"><img src="https://avatars.githubusercontent.com/u/64764136?v=4" title="DestinyWolf" width="50" height="50"></a>

<details>
<summary><h2>Índice</h2></summary>

- [Instalação](#instalação)
	-  [Pré-requisitos](#pré-requisitos)
-  [Softwares utilizados](#softwares-utilizados)
	- [Linguagem C](#linguagem-c)
	- [Compilador GNU](#compilador-gnu)
 	- [VS Code](#vs-code)
- [DE1-SoC](#kit-de-desenvolvimento-de1-soc)
	- [Visão geral da DE1-SoC](#visão-geral-da-de1-soc)
  	- [Sistema computacional da placa](#sistema-computacional-de1-soc)
- [Processador gráfico](#processador-gráfico)
	- [Instruções](#instruções)
- [Solução geral](#solução-geral)
- [Driver CoLenda](#driver-colenda)
- [Biblioteca CoLenda](#biblioteca-colenda)
	- [Constantes de sprites](#constantes-de-sprite)
	- [Structs](#structs)
  - [Funções](#funções)
  - [Pseudo-instruções](#pseudo-instruções)
  - [Funções internas auxiliares](#funções-internas-auxiliares)
  - [Validação de valores](#validação-de-valores)
- [Exemplos](#exemplos)
- [Testes](#testes)
	- [Teste de background e limite máximo de posição de polígonos](#teste-de-background-e-limite-máximo-de-posição-de-polígonos)
	- [Teste de limite máximo de posição de polígonos](#teste-de-limite-máximo-de-posição-de-polígonos)
	- [Teste com blocos de background](#teste-com-blocos-de-background)
- [Conclusão](#conclusão)
- [Referências](#referências)
 
</details>

## Instalação
<details>
<summary><h3>Pré-requisitos</h3></summary>

- Possuir conexão com internet;
- Possuir instalado o compilador gcc;
- Possuir instalado o Git;
- Utilizar uma placa de desenvolvimento FPGA DE1-SoC;
- Possuir o processador gráfico CoLenda na FPGA;
- Possuir um monitor conectado à placa por meio da saída VGA

</details>

#### 1. Clonar o repositório
Abra o terminal do seu dispositivo e execute o seguinte comando:
```
git clone https://github.com/camilaqPereira/coLenda_driver.git
```
**Transfira os arquivos do projeto para a placa DE1-SoC.**

#### 2. Acessar a pasta */source/driver* e compilar o driver
Para acessar a pasta */source/driver* e compilar o módulo kernel na placa, basta executar os seguintes comandos:
```
cd /source/driver
make all
```
#### 3. Carregar o módulo kernel
Na placa, execute os comandos:
```
sudo su
insmod colenda_driver.ko
```
#### 4. Buscar o valor major alocado dinamicamente
Execute o comando abaixo na placa e identifique o major associado ao driver colenda.
```
cat /proc/devices
```
#### 5. Criar o device file
Execute os seguintes comandos na placa:
```
sudo su
mknod /dev/colenda c [MAJOR] 0
```
#### 6. Inclua a biblioteca CoLenda no seu código
Adicione o seguinte include no seu código:
```C
#include "/.../coLenda_driver/source/Lib/colenda.h"
```
## Softwares utilizados

<details>
<summary> <b>Linguagem C</b> </summary>

### Linguagem C

É uma linguagem de programação de propósito geral que combina abstrações e controles de baixo nível sobre o hardware resultando em ganho de eficiência. O software criado em 1970 por Dennis Ritchie é estreitamente associada ao sistema operacional UNIX, uma vez que as versões desse sistema foram escritas em linguagem C. Além disso, a sintaxe simples e a alta portabilidade desta linguagem entre dispositivos contribui para seu amplo uso em sistemas embarcados de recursos limitados.

</details>

<details>
<summary> <b>Compilador GNU</b> </summary>

### Compilador GNU

O GNU Compiler Collection GCC (Coleção de Compiladores GNU), ou GCC, é um conjunto de compiladores de código aberto desenvolvido pelo Projeto GNU que oferecem suporte a uma gama de linguagens de programação, incluindo C, C++, Fortran, Ada e Go. Esta ferramenta otimiza a compilação, ou seja a produção de código de máquina, nas várias linguagens e arquiteturas de processadores suportadas.

</details>
<details>

<summary> <b>VS Code</b> </summary>

### VS Code

O Visual Studio Code, ou VS Code, é um editor de texto gratuito com suporte a várias linguagens de programação, incluindo Python, Java, C, C++ e JavaScript. A ferramenta desenvolvida pela Microsoft Corporation dispõe de diversos recursos de depuração, destaque de erros, sugestões, personalização dentre outros para auxiliar a codificação.

</details>

## Kit de desenvolvimento DE1-SoC

<details>
<summary><b>Visão geral da DE1-SoC</b></summary>

### Visão geral da DE1-SoC

Equipado com processador, USB, memória DDR3, Ethernet e uma gama de periféricos, o kit de desenvolvimento DE1-SoC (Figura 1) integra no mesmo Cyclone® V da Intel®, sistema em chip (SoC), um *hard processor system* (HPS) a uma FPGA (*Field Programmable Gate Arrays*). Este design permite uma grande flexibilidade da placa nas mais variadas aplicações. Para o acesso ao sistema operacional Linux embarcado na placa, o protocolo de rede SSH *(Secure Shell)* foi utilizado, estabelecendo uma conexão criptografada para comunicação entre a placa e computador *host*.

<div align="center">
  <figure>  
    <img src="docs/images/kit_desenvolvimento_DE1-SoC.jpg" width="600px">
    <figcaption>
      <p align="center"> 

[**Figura 1** - Kit de Desenvolvimento DE1-SoC](https://fpgacademy.org/index.html)

</p>
    </figcaption>
  </figure>
</div>

</details>

<details>
<summary><b>Sistema computacional DE1-SoC</b></summary>

### Sistema computacional DE1-SoC

<div align="center">
  <figure>  
    <img src="docs/images/diagramaDE1SoC_FPGAcademy.png" width="500px">
    <figcaption>
      <p align="center">

[**Figura 2** - Diagrama de Blocos da DE1-SoC](https://fpgacademy.org/index.html)

</p>
    </figcaption>
  </figure>
</div>

O diagrama de blocos do sistema computacional, apresentado na figura 2,  explicita os componentes do Cyclone® V da Intel®, bem como suas conexões. O HPS inclui um processador ARM® Cortex-A9 MPCore™ de 2 núcleos com uma distribuição Linux embarcada destinada a processamentos de propósito geral,  além da memória DDR3 e dos dispositivos periféricos. Já a FPGA possibilita uma variedade de implementações através da programação dos blocos lógicos.


> A comunicação bidirecional entre a o HPS e a FPGA se dá por meio das *FPGA bridges*. 
> No sentido HPS-FPGA, todos os dispositivos de entrada e saída (E/S) conectados à FPGA são acessíveis ao processador através do mapeamento de memória.
> As informações sobre o endereçamento dos periféricos estão disponíveis na [documentação da placa](https://fpgacademy.org/index.html).

</details>

## Periféricos utilizados
O kit de desenvolvimento DE1-SoC possui diversos periféricos integrados. Neste projeto, utilizou-se apenas a saída VGA conectada a um monitor de tubo CRT - *Cathode Ray Tube* -  com resolução de 640×480 pixels (figura 3) e uma taxa de atualização de 60Hz.

<div align="center">
    <img src="docs/images/vga-placa.jpg" height="400px">
    <img src="docs/images/monitor.jpg" height="400px">
</div>
<div align="center">

  **Figura 3** - Monitor utilizado (esquerda) e a conexão VGA com a placa (direita)

</div>

<details>
<summary><b>Padrão VGA</b></summary>

### Padrão VGA

O padrão VGA é um modelo bastante utilizado, estando presente principalmente nos monitores do tipo CRT.
Este padrão é composto pela transmissão de sinais de geração de vídeo e sinais de cores (RGB - red, green, blue). Segue abaixo a especificação dos dois sinais de geração de vídeo:
- sinal de sincronismo horizontal (*hsync*): indica o tempo necessário para percorrer uma linha do monitor;
- sinal de sincronismo vertical (*vsync*): indica o tempo necessário para percorrer toda a tela (finalização de um frame);

Neste padrão, um frame é definido pelos parâmetros indicados na figura 4:
- área ativa: espaço de exibição dos pixels na tela;
- front e back porches: tempos de espera a serem implementados para delimitar a região ativa

<div align="center">
  <figure>  
    <img src="docs/images/frame.PNG">
    <figcaption>
      <p align="center">

[**Figura 4** - Representação de um frame por meio do padrão VGA](https://drive.google.com/file/d/1MlIlpB9TSnoPGEMkocr36EH9-CFz8psO/view)

</p>
    </figcaption>
  </figure>
</div>

Estes parâmetros são calculados utilizando a resolução e taxa de atualização dos monitores. Os cálculos para a definição dos valores utilizados no projeto estão disponíveis na [seção III.C deste arquivo](https://drive.google.com/file/d/1MlIlpB9TSnoPGEMkocr36EH9-CFz8psO/view). As especificações de parâmetros para diferentes resoluções podem ser encontrados no [manual da placa](https://fpgacademy.org/index.html)

</details>

<details>
<summary><b>Saída VGA na Placa</b></summary>

### Saída VGA na Placa
Na placa DE1-SoC, os sinais de sincronização são gerados diretamente pela Cyclone V SoC FPGA, com a conversão digital-analógica sendo feita por meio de Analog Devices ADV7123 para a representação das 3 cores RGB. 
Cada canal de cor RGB é representado por 8 bits e os sinais *hsync* e *vsync* são representados por 1 bit cada.
 

<div align="center">
  <figure>  
    <img src="docs/images/vga_placa.PNG">
    <figcaption>
      <p align="center">

[**Figura 5** - Conexões entre FPGA e VGA](https://fpgacademy.org/index.html)

</p>
    </figcaption>
  </figure>
</div>
</details>


> Os sinais de geração de vídeo e de cores são controlados pelo *Controlador VGA* implementado pelo processador CoLenda.

## Processador gráfico

O processador gráfico CoLenda foi desenvolvida pelo discente Gabriel Sá Barreto Alves como parte 
do seu trabalho de conclusão de curso (TCC) na Universidade Estadual de Feira de Santana (UEFS). O dispositivo gráfico permite o controle de polígonos convexos (triângulos e quadrados) e sprites em um monitor VGA com resolução de 640x480 pixels. No projeto desenvolvido para o TCC, o NIOS II foi utilizado como unidade de processamento principal.

> [!NOTE]
> No presente projeto, o NIOS II foi substituído pelo HPS da placa DE1-SoC.

Além do controle de polígonos e sprites, a GPU CoLenda permite alterar a cor de fundo do monitor, alterar blocos de fundo de dimensão 8x8 e criar sprites próprios.

<details>
	<summary><b>Instruções</b></summary>

### Instruções
Para realizar as atividades especificadas anteriormente, a GPU disponibiliza um conjunto de instruções, cada uma com tamanho e campos diferentes. A tabela abaixo lista as instruções disponíveis, assim como suas funções.  
<div align="center">

|Sigla|                    Instrução                    |                Função                  |
|:---:|                  :-----------:                  |           :----------------:           |  
| WBR |          Escrita no banco de registradores      |Configuração dos registradores que armazenam os sprites e a cor de background |
| WSM |          Escrita na memória de sprites          |Armazemento ou modificação na memória de sprites|
| WBM |          Escrita na memória de backgroung       |Configuração dos valores RGB para as áreas do background| 
|  DP |Escrita na memória de instrução do co-processador|Definição dos dados de um polígono a ser renderizado|

</div>
</details>

<details>
<summary><b>Comunicação com o processador gráfico</b></summary>

### Comunicação com o processador gráfico

<div align="center">
  <figure>  
	<img src="docs/images/diagrama_gpu.png" width="500px">
	<figcaption>
	<p align="center">
  
  [**Figura 6** - Representação da arquitetura da GPU CoLenda](https://drive.google.com/file/d/1MlIlpB9TSnoPGEMkocr36EH9-CFz8psO/view)
  
  </p>
	</figcaption>
  </figure>
</div>

A comunicação com o processador gráfico dá-se por meio dos barramentos de dados data A e data B (figura 6). O barramento data A é utilizado para transmissão dos dados de acesso à memória e registradores e dos códigos de operações. Já o data B é utilizado para transmissão dos demais dados customizáveis tais como cores e posição. Além disso, o dispositivo apresenta os seguintes sinais de controle:
- sinal de escrita na fila de instruções (input);
- reinicialização de contador externo (input);
- sinal que indica que a fila de instruções está cheia (output);
- sinal que indica quando uma tela finalizou a renderização (output).

</details>

## Solução geral

<div align="center">
  <figure>  
    <img src="docs/images/solucao_geral.png">
    <figcaption>
      <p align="center"><b>Figura 7</b> - Esquema em blocos da solução geral </p>
    </figcaption>
  </figure>
</div>

O produto desenvolvido implementa a intercomunicação entre o software e o dispositivo gráfico CoLenda. O fluxo de comunicação entre a
aplicação de usuário, o módulo kernel e o hardware é esquematizado na figura 7. O fluxo de comunicação inicia-se com a aplicação do
usuário que, por meio dos recursos disponibilizados pela biblioteca CoLenda tais como structs e funções, gerencia os dados
dos elementos a serem exibidos no monitor VGA e as chamadas das respectivas funções da *lib* para realizar as exibições na tela.

Por sua vez, a biblioteca atua como uma mediadora entre a aplicação de usuário e o driver CoLenda, gerenciando as chamadas de sistema
necessárias, assim como as conversões das solicitações recebidas para o stream de caracteres a ser passado ao driver.
Por fim, o driver gerencia os sinais de controle e o barramento de dados do hardware, a fim de enviar as instruções recebidas da biblioteca.

## Driver CoLenda

A implementação e compreensão do driver CoLenda como um módulo carregável mediante a demanda perpassa por alguns conceitos fundamentais, como a arquitetura do sistema operacional Linux, que serão explicitados a seguir

### Background
<details>
<summary><b>Arquitetura do Sistema Operacional Linux</b></summary>

#### Arquitetura do Sistema Operacional Linux

Existem dois modos de operação referentes ao modo de execução do processador: modo núcleo (ou modo kernel) e modo usuário. O kernel é parte do sistema operacional que tem acesso completo a todo o hardware e recursos, podendo executar qualquer instrução disponível na máquina. Portanto, o modo kernel possui privilégios de acesso e execução de subsistemas. Já o modo usuário possui  limitações e menos privilégios. 

</details>

### Arquitetura do Sistema Operacional Linux

A figura 8 exibe uma típica arquitetura do sistema operacional linux, onde o espaço kernel intermedia o acesso e o compartilhamento dos recursos de hardware, de maneira segura e justa, entre múltiplas aplicações. A janela de intereção entre o espaço de usuário e do kernel se dá através de uma interface de chamadas de sistema em que, em mais alto nível, o kernel prove "serviços" às aplicações. Além do kernel, responsável pelo gerenciamento de processos, segurança, gerenciamento de memória e demais atribuições do sistema operacional, os drivers de dispositivos também compõem o espaço do kernel. 
<div align="center">
  <figure>  
  <img src="docs/images/arquitetura-so.jpg">
  <figcaption>
  <p align="center">
  
  [**Figura 8** - Esquema em blocos da arquitetura típica de sistemas operacionais(adaptado)](https://linux-kernel-labs.github.io/refs/heads/master/lectures/intro.html)

  <p>
  </figcaption>
  </figure>
</div>

<details>
<summary>Mapeamento de Memória</summary>

#### Mapeamento de Memória

Como apresentado na figura 6, o processador gráfico recebe os sinais dataA, dataB, wrreg, reset_pulse_counter bem como envia os sinais screen e wfull, cujos endereços base dos barramentos da GPU são respectivamente 0x80, 0x70, 0xc0, 0x90, 0xa0 e 0xb0. Para a criação e utilização do mapeamento de memória são manipuladas a ponte <code>ALT_LWFPGASLVS_OFST</code> (0xFF200000)(Lightweight HPS-to-FPGA Bridge), encarregada da conexão entre o FPGA e o HPS da placa, juntamente com a <code>HW_REGS_BASE</code> (0xFC000000), que armazena o endereço base para os registradores de acesso aos periféricos do HPS e a <code>HW_REGS_SPAN</code> (0x04000000), encarregada do armazenamento em bytes da região de memória a ser mapeada. 
Entretanto, para acessar os valores das portas mapeadas, faz-se necessária a virtualização destes endereços físicos.
<div align="center">
  <figure>  
    <img src="docs/images/memory-mapping.png" width="800">
    <figcaption>
      <p align="center"><b>Figura 9 - </b>Mapeamento de memória via MMU</p>
    </figcaption>
  </figure>
</div>

A memória virtual é uma técnica utilizada para gerenciamento de memória nos computadores. Nela, cada programa possui seu próprio espaço de endereçamento o qual é mapeado na memória física. Quando o programa referencia uma parte do espaço de endereçamento que está na memória física, o hardware encarrega-se de realizar rapidamente o mapeamento (tradução). 
Para realizar o mapeamento do endereço físico dos barramentos e sinais, foram utilizadas as funções `ioremap()` e `iounmap()`. A partir do endereço virtual gerado, pode-se receber e enviar dados para o processador gráfico.
</details>

<details>
<summary>Driver do Dispositivo</summary>
#### Driver do Dispositivo
</details>
O <i>driver</i> é uma abstração para acesso a um dispositivo de hardware que permite uma infraestrutura de interação com o aparato físico. Apesar da possibilidade de drivers sendo executados no espaço de usuário, eles são geralmente executados no espaço do kernel como módulo kernel, que podem ser carregados e descarregados em tempo de excução.

Em sistemas UNIX, dispositivos de hardware são acessados pelo usuário através da sua abstração em arquivos especiais, que estão associados ao correspondente driver e hardware como representa na figura 10. Esse arquivos estão disponíveis e agrupados no diretório <code>/dev</code> e cada chamada de sistem como `open`, `read`, `write` etc. é redirecionada pelo sistema operacional para driver que faz o gerenciamento do dispositivo físico.

<div align="center">
  <figure>  
  <img src="docs/images/driver-abstraction.png">
  <figcaption>
  <p align="center">
  
  [**Figura 10** - Esquema em alto nível da associação entre arquivo especial, driver e dispositivo (adaptado)](https://linux-kernel-labs.github.io/refs/heads/master/lectures/intro.html)
  
  </p>
  </figcaption>
  </figure>
</div>

Nas distribuições UNIX, os drivers de dispositivos e seus arquivos podem ser do tipo *caractere* ou *bloco*. A principal diferença entre eles se dá pelo fato dos drivers de caracteres manipularem uma pequena quantidade de dados, geralmente strings de bytes, para dispositivos como mouse, teclado e portas seriais. Já o segundo tipo, acessa e transfere um grande volume de dados organizados em blocos, além de necessitarem de buffering. A exemplo tem-se drivers para disco rígido, memória RAM, etc. Desse modo, o driver CoLenda para comunicação com o processador gráfico é do tipo caractere.

Além disso, os dispositivos tem uma identificação característica composta pelo *major* e *minor number*. O *major number* identifica o tipo do dispositivo e o *minor* cada dispositivo físico associado ao driver. Ou seja, caso existam vários dispositivos do mesmo tipo eles terão o mesmo *major number*, porém *minors* diferentes para cada um deles.

Dessa maneira, ao acessar o arquivo especial do dispositivo, uma chamada de sistema é realizada e o driver associado realiza a operação de leitura ou escrita de dados no equipamento físico, como é representado na figura 11.
<div align="center">
  <figure>  
  <img src="docs/images/infraestrutura-driver.png">
  <figcaption>
  <p align="center">
  
  [**Figura 11** - Esquema em blocos das chamadas de sistema ao dispositivo (adaptado)](https://linux-kernel-labs.github.io/refs/heads/master/lectures/intro.html)
  
  </p>
  </figcaption>
  </figure>
</div>

## Biblioteca CoLenda

A biblioteca desenvolvida provê uma abstração da comunicação com o driver de dispositivo, facilitando a interação do usuário com o 
módulo kernel do hardware. Esta *lib* disponibiliza constantes para a seleção de sprites, estruturas para a organização dos elementos a
serem exibidos, funções respectivas às instruções do processador gráfico e pseudo-instruções, tal como *clear*, que executam conjuntos de instruções.
> [!NOTE]
> Os sprites disponíveis para seleção estão salvos em hardware no processador gráfico.
> Nenhum deles foi criado pela biblioteca

> [!NOTE]
> As pseudo-instruções são funções da biblioteca que podem ser chamadas

<details >
<summary><b>Constantes de sprite</b></summary>

### Constantes de sprite
As constantes de sprite implementadas visam facilitar a escolha do sprite, pois abstraem o número relacionado ao endereço em que um sprite específico está localizado.

| Define    | Valor    | sprite associado
|-----------|----------|-------------------
| ORANGE_BLOCK  | 0     | bloco laranja
| BLUE_BLOCK  	| 1     | bloco azul
| MEDAL			| 2		| medalha
| BOMB 			| 3		| bomba
| TREE			| 4 	| arvore
| SHIP_UP 		| 5 	| nave virada para cima
| SHIP_RIGTH 	| 6 	| nave virada para direita
| SHIP_DOWN		| 7		| nave virada para baixo
| SHIP_LEFT		| 8 	| nave virada para esquerda
| COIN			| 9		| moeda
| DIAMOND		| 10	| diamante
| LASER_VERTICAL| 11 	| laser na vertical
| LASER_DIAGONAL1| 12 	| laser na diagonal principal
| LASER_HORIZONTAL| 13 	| laser na horizontal
| LASER_DIAGONAL2| 14 	| laser na diagonal secundária
| HEART			| 15	| coração azul
| LOG			| 16	| tronco de arvore
| BLUE_CAR		| 17	| carro de corrida azul
| GREEN_CAR		| 18	| carro de corrida verde
| PURPLE_CAR	| 19	| carro de corrida roxo
| YELLOW_CAR	| 20	| carro de corrida amarelo
| ALIEN1		| 21	| alien do space invaders
| ALIEN2		| 22	| alien do space invaders
| DRAGON		| 23	| pedra
| CUP			| 24	| troféu

a baixo segue as imagens dos sprites que estão na memporia

<img src="docs/images/sprites.png" style="">
<p><b>Figura 9</b> - tabela com os sprites pre-renderizados na gpu</p>
<p>Fonte: Arquivo auxiliar disponibilizado pelos professores</p>

</details>

<details>
<summary><b>Structs</b></summary>

### Structs

| Struct      | Descrição | Atributos |
| ---- | ----------- | ----------- |
| Cor      | Define os campos que uma cor deve possuir. Utilizada nas demais estruturas que necessitam de um campo de cor| Vermelho, verde e azul |
| Sprite   | Define os dados necessários para a exibição de um sprite        | Coordenadas x e y, offset (para a escolha do sprite), registrador (espaço de memória que será ocupado) e visibilidade |
| Bloco de background   | Agrupa as informações necessárias para a edição de um bloco de blockground | Cor (struct) e coordenadas x e y  |
| Pixel   | Define as informações necessárias para a criação de um pixel de um sprite. Localizado na memória de sprites      | Endereço de memória e cor (struct) |
| Polígono   | Agrupa as informações necessárias para a exibição de um polígono   | Coordenadas x e y, camada, tamanho, forma (triângulo ou quadrado e cor (struct) |


<blockquote>

**NOTE**

As coordenadas de sprites são relativas a disposição dos pixels na tela (640x480). Já as coordenadas dos blocos de blackground são relativas à disposição dos blocos de tamanho 8x8 pixels (totalizando 80x60 blocos). Cada bloco possui um endereço na memória 
</blockquote>

</details>

<details >
<summary ><b>Funções</b></summary>

### Funções 
	
|      Função          |          Argumento         | Instrução relacionada |
|     -----------      |        -----------         |           ----        |
|   Setar pixel        |         Struct pixel       |           WSM         |
|  Setar cor de fundo  |         Struct cor         |           WRB         |
| Setar bloco de fundo | Struct bloco de background |           WSM         |
|    Setar sprite      |       Struct sprite        |           WRB         |
|    Setar polígono    |      Struct polígono       |           DP          |
	
</details>

<details>
<summary ><b>Pseudo-instruções</b></summary>
	
### Pseudo-instruções 
	
| Função | Descrição | Argumento |
|  -----------  | ----------- |----------- |
| Desenhar linha vertical | Desenha uma linha vertical utilizando blocos de background. Chama a função setar bloco de background n vezes alterando apenas a coordenada y | Coordenadas iniciais x e y, tamanho (n) e  cor (struct)|
| Desenhar linha horizontal | Desenha uma linha horizontal utilizando blocos de background. Chama a função setar bloco de background n vezes alterando apenas a coordenada x | Coordenadas iniciais x e y, tamanho (n) e  cor (struct)|
| Desenhar bloco de background | Seta um bloco de background. Dispensa a instância da struct| Coordenadas iniciais x e y, e cor (struct)|
| Clear | Reseta a tela| - |

</details>

<details >
<summary><b>Funções internas  auxiliares</b></summary>

### Funções internas auxiliares

- função para escrever no buffer do driver as instruções (gerencia a chamada de sistema write)
- função para transformar 2 wchar_t em uma string de 8 char

</details>

<details >
<summary ><b>Validação de valores</b></summary>

###  Validação de valores e tratamento de erros

A biblioteca apresenta recursos para validação dos valores inseridos pelo usuário, pois como as instruções possuem tamanhos e campos distintos, foi imprescindível a existência de recursos para validar essas informações. A detecção de um erro retorna um valor de erro à aplicação do usuário  e exibe no terminal o erro uma mensagem referente ao erro ocorrido

</details>	

## Exemplos
Apesar do número limitado de elementos disponibilizados pelo processador gráfico, uma vasta gama de imagens podem ser renderizadas. Um exemplo de imagem que pode ser criada
é mostrada na figura 4 na qual foram utilizados todos os recursos do hardware:
- polígonos: usados para desenhar os botões direitos do gameboy
- cor de background: definido para branco
- blocos de background: usados para desenhar o corpo, a tela e os botões esquerdos do gameboy
- sprites: usados para criar o cenário na tela do gameboy

As pseudo instruções foram todas utilizadas para facilitar o desenvolvimento da imagem. O código para a renderização da imagem encontra-se [aqui](source/Lib/gameboy_example.c).

<div align="center">
  <figure>  
    <img src="docs/images/gameboy.jpg" height="500px">
    <figcaption>
      <p align="center"><b>Figura 10</b> - Imagem exibida no monitor</p>
      <p align="center">Fonte: Elaboração própria</p>
    </figcaption>
  </figure>
</div>

>[!TIP]
> Loops e alteração da posição dos elementos podem ser usadas para criar imagens dinâmicas!

> [!TIP]
> Como a GPU aceita cores no formato RGB de 9 bits, utilize a tabela de cores disponível
> [aqui](arquivos_complementares/9-bit-rgb-palette.html) para falicitar a seleção das cores a serem usadas na sua imagem.

## Testes

Testar a exibição dos recursos da GPU no monitor é verificar que a biblioteca CoLenda realiza a montagem correta das instruções a serem
passadas para o driver, bem como o gerenciamento correto das chamadas de sistema. É verificar também que o módulo kernel CoLenda realiza
o mapeamento adequado do barramento de dados do harware, assim como o gerenciamento preciso dos sinais de controle do processador para a
exibição dos elementos na tela.

Este processo consiste na instanciação das structs dos elementos, chamada das respectivas funções de exibição e conferência dos dados
obtidos na tela.  


<details>
	<summary><b>Teste de background e limite máximo de posição de polígonos</b></summary>

## Teste de background e limite máximo de posição de polígonos
Neste caso, o trecho de código abaixo foi utilizado e, como resultado, espera-se que a cor de fundo seja definida para branco e um
triângulo preto de tamanho 20x20 seja exibido na posição (511, 240). Como observa-se na figura 5, os devidos elementos foram setados com as configurações corretas. 

```C
// inicia a comunicação com o driver
GPU_open();

//Instanciação de structs
color_t white = {7,7,7};
color_t black = {0, 0, 0};

polygon_t black_triangle = {511,240, 0, 1, 1, black};

//seta a cor de fundo do background
set_background_color(white);

//seta o polígono
set_polygon(black_triangle);

//encerra a comunicação com o driver
GPU_close();
```

<div align="center">
  <figure>  
    <img src="docs/images/poligono_limite.jpg" height="500px">
    <figcaption>
      <p align="center"><b>Figura 11</b> - Resultado do teste no monitor</p>
      <p align="center">Fonte: Elaboração própria</p>
    </figcaption>
  </figure>
</div>

<blockquote>

**WARNING**

O tamanho do campo coordenada x da instrução DP (9 bits) restringe as posições que os polígonos
podem ocupar. O triânguloda figura 5 ilustra a posição limite, no eixo x, que os polígonos podem 
ocupar. 

</blockquote>
 
</details>

<details>
<summary><b>Teste de limite máximo de posição de polígonos</b></summary>

### Teste de limite máximo de posição de polígonos
Neste caso, o mesmo trecho de código da seção anterior foi utilizado  alterando-se apenas as coordenas x e y do polígono. Como resultado, esperava-se que a cor de fundo fosse definida para branco e um triângulo preto de tamanho 20x20 fosse exibido na posição 
(10, 10). Como observa-se na figura 6, o 
triângulo não foi setado corretamente. O teste foi repetido com o quadrado e o erro persistiu (figura 7). 
Após diversas análises e múltiplos testes, concluiu-se que o erro pertence à GPU. Todos os polígonos cujas coordenadas x e/ou y sejam menores que metade do tamanho do polígono não são exibidos ou sua exibição assume um tamanho aleatório devido a erros nos cálculos.

<div align="center">
  <figure>  
    <img src="docs/images/triangulo_bug.jpg" height="500px">
    <figcaption>
      <p align="center"><b>Figura 12</b> - Resultado do teste com triângulo no monitor</p>
      <p align="center">Fonte: Elaboração própria</p>
    </figcaption>
  </figure>
</div>

<div align="center">
  <figure>  
    <img src="docs/images/quadrado_bug.jpg" height="500px">
    <figcaption>
      <p align="center"><b>Figura 13</b> - Resultado do teste com quadrado no monitor</p>
      <p align="center">Fonte: Elaboração própria</p>
    </figcaption>
  </figure>
</div>
	
</details>


<details>
<summary><b>Teste com blocos de background</b></summary>

### Teste com blocos de background
Neste caso, o trecho de código abaixo foi utilizado para testar os limites de representação dos blocos de background. Como resultado, esperava-se que um erro ocorresse o que não aconteceu.
Novos testes foram repetidos e, a partir disto, concluiu-se que o endereçamento dos blocos de background contem 13 bits, ao invés dos 12 especificados na documentação. Na figura 8, estão destacados todos os blocos de background que não seriam abrangidos caso o endereçamento tivesse 12 bits. 

```C
// inicia a comunicação com o driver
GPU_open();

//Instanciação de structs
color_t blue = {0, 0, 3};

//Seta bloco de background
draw_background_block(70,57, blue);
//encerra a comunicação com o driver
GPU_close();
```

<div align="center">
  <figure>  
    <img src="docs/images/12bits.jpg" height="500px">
    <figcaption>
      <p align="center"><b>Figura 14</b> - Resultado do teste dos limites de representação dos blocos de background no monitor</p>
      <p align="center">Fonte: Elaboração própria</p>
    </figcaption>
  </figure>
</div>
</details>

## Conclusão
Após diversos testes foi concluído que tanto o drive quanto a biblioteca atenderam aos objetivos esperados, e desempenharam de maneira satisfatória a intercomunicação usuário-driver- dispositivo. 

Durante os testes foi notado um possível problema com a situação da fila de instrução cheia e para isso foi implementado um delay a cada 12 instruções na biblioteca. Como melhoria futura, pode-se implementar tratamentos alternativos no driver para que este consiga lidar  sozinho com problemas de mesmo cunho.

Além de compreender as políticas de gerenciamento de sistema operacional Linux em arquitetura ARM e utilizar a interface de conexão entre HPS e FPGA da DE1-SoC, este projeto proporcionou o aprofundamento e prática em uma distribuição Linux embarcada e dos conceitos de interação entre hardware e software.

## Referências
ALVES, Gabriel - [Desenvolvimento de uma Arquitetura Baseada em Sprites para criacão de Jogos 2D em Ambientes reconfiguraveis utilizando dispositivos FPGA.](https://drive.google.com/file/d/1MlIlpB9TSnoPGEMkocr36EH9-CFz8psO/view) Orientador: DIAS, Afranserai, SARINHO, Vitor. 2024. Trabalho de Conclusão de Curso - Engenharia da Computação, UEFS, Feira de Santana. Acessado em: 14 maio. 2024. 

[Character device drivers — The Linux Kernel documentation.](https://linux-kernel-labs.github.io/refs/heads/master/labs/device_drivers.html) 

[Introduction — The Linux Kernel documentation](https://linux-kernel-labs.github.io/refs/heads/master/lectures/intro.html)

TANENBAUM, A. S.; BOS, Herbert. Sistemas operacionais modernos. 4. ed. São Paulo: Pearson Education do Brasil, 2016. Acesso em: 30 maio. 2024.

[History and Evolution of GPU Architecture](https://www.igi-global.com/chapter/history-and-evolution-of-gpu-architecture/139841)

[GPU computing](https://escholarship.org/content/qt0cv1p1nc/qt0cv1p1nc_noSplash_e93469c5acbe804c7c045217eee807bb.pdf)

