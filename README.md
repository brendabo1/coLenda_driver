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
[Biblioteca](README.md#biblioteca-colenda) • [Exemplo de utilização](#exemplo-de-utilização) • [Testes](README.md#testes)

</div>

## Sobre o projeto

A Unidade de Processamento Gráfico (GPU) é um microprocessador especializado e paralelo dedicado à aceleração de computações gráficas. Este processador foi desenvolvido especificamente 
para a realização de diversas operações com valores de ponto flutuante, essenciais para o processamento de gráficos 2D/3D. Atualmente, as GPUs, além de serem potentes dispositivos 
gráficos, são processadores paralelos altamente programáveis que apresentam alta precisão e poderosos recursos.

Neste contexto de grande evolução das unidades de processamento gráfico e de crescente popularidade dessas, o presente projeto implementa um de um módulo kernel para o processador 
gráfico CoLenda na HPS do kit de desenvolvimento DE1-SoC. Além disso, implementa também uma biblioteca para facilitar a utilização do driver.

<details>
<summary> <h3>Requisitos</h3></summary>
	
O presente projeto deve atender às condições e aos requisitos predeterminados, de modo que:
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
- [Periféricos utilizados](#periféricos-utilizados)
	- [Padrão VGA](#padrão-vga)
 	- [Saída VGA no DE1-SoC](#saída-vga-na-placa) 
- [Processador gráfico](#processador-gráfico)
	- [Instruções](#instruções)
 	- [Comunicação como processador gráfico](#comunicação-com-o-processador-gráfico) 
- [Solução geral](#solução-geral)
- [Driver CoLenda](#driver-colenda)
		- [Background](#-background)
 		- [Arquitetura do Sistema Operacional Linux](#arquitetura-do-sistema-operacional-linux)
		- [Mapeamento de memória](#mapeamento-de-memória)
 		- [Driver de dispositivo](#driver-de-dispositivo)
  	- [Driver desenvolvido](#driver-desenvolvido)
- [Biblioteca CoLenda](#biblioteca-colenda)
	- [Constantes de sprites](#constantes-de-sprite)
	- [Structs](#structs)
  	- [Funções correspondentes às instruções](#funções-correspondentes-às-instruções)
  	- [Funções de pseudo-instruções](#funções-de-pseudo-instruções)
  	- [Funções internas auxiliares](#funções-internas-auxiliares)
  	- [Validação de valores e tratamento de erros](#validação-de-valores-e-tratamento-de-erros)
- [Exemplo de utilização](#exemplo-de-utilização)
- [Testes](#testes)
	- [Setando background](#setando-background)
  	- [Setando polígonos](#setando-polígonos)
 	- [Teste de sobreposição de polígonos](#teste-de-sobreposição-de-polígonos)
  	- [Teste de limite máximo de posição de polígonos](#teste-de-limite-máximo-de-posição-de-polígonos)
	- [Teste de limite mínimo de posição de polígonos](#teste-de-limite-mínimo-de-posição-de-polígonos)
	- [Teste com blocos de background](#teste-com-blocos-de-background)
 	- [Teste com a função clear](#teste-com-a-função-clear)
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

É uma linguagem de programação de propósito geral que combina abstrações e controles de baixo nível sobre o hardware resultando em ganho de eficiência. O software criado em 1970 por 
Dennis Ritchie é estreitamente associada ao sistema operacional UNIX, uma vez que as versões desse sistema foram escritas em linguagem C. Além disso, a sintaxe simples e a alta 
portabilidade desta linguagem entre dispositivos contribui para seu amplo uso em sistemas embarcados de recursos limitados.

</details>

<details>
<summary> <b>Compilador GNU</b> </summary>

### Compilador GNU

O GNU Compiler Collection GCC (Coleção de Compiladores GNU), ou GCC, é um conjunto de compiladores de código aberto desenvolvido pelo Projeto GNU que oferecem suporte a uma gama de 
linguagens de programação, incluindo C, C++, Fortran, Ada e Go. Esta ferramenta otimiza a compilação, ou seja a produção de código de máquina, nas várias linguagens e arquiteturas de 
processadores suportadas.

</details>
<details>

<summary> <b>VS Code</b> </summary>

### VS Code

O Visual Studio Code, ou VS Code, é um editor de texto gratuito com suporte a várias linguagens de programação, incluindo Python, Java, C, C++ e JavaScript. A ferramenta desenvolvida 
pela Microsoft Corporation dispõe de diversos recursos de depuração, destaque de erros, sugestões, personalização dentre outros para auxiliar a codificação.

</details>

## Kit de desenvolvimento DE1-SoC

<details>
<summary><b>Visão geral da DE1-SoC</b></summary>

### Visão geral da DE1-SoC

Equipado com processador, USB, memória DDR3, Ethernet e uma gama de periféricos, o kit de desenvolvimento DE1-SoC (Figura 1) integra no mesmo Cyclone® V da Intel®, sistema em chip 
(SoC), um *hard processor system* (HPS) a uma FPGA (*Field Programmable Gate Arrays*). Este design permite uma grande flexibilidade da placa nas mais variadas aplicações. Para o acesso 
ao sistema operacional Linux embarcado na placa, o protocolo de rede SSH *(Secure Shell)* foi utilizado, estabelecendo uma conexão criptografada para comunicação entre a placa e 
computador *host*.

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

O diagrama de blocos do sistema computacional, apresentado na figura 2,  explicita os componentes do Cyclone® V da Intel®, bem como suas conexões. O HPS inclui um processador ARM® 
Cortex-A9 MPCore™ de 2 núcleos com uma distribuição Linux embarcada destinada a processamentos de propósito geral,  além da memória DDR3 e dos dispositivos periféricos. Já a FPGA 
possibilita uma variedade de implementações através da programação dos blocos lógicos.


> A comunicação bidirecional entre a o HPS e a FPGA se dá por meio das *FPGA bridges*. 
> No sentido HPS-FPGA, todos os dispositivos de entrada e saída (E/S) conectados à FPGA são acessíveis ao processador através do mapeamento de memória.
> As informações sobre o endereçamento dos periféricos estão disponíveis na [documentação da placa](https://fpgacademy.org/index.html).

</details>

## Periféricos utilizados
O kit de desenvolvimento DE1-SoC possui diversos periféricos integrados. Neste projeto, utilizou-se apenas a saída VGA conectada a um monitor de tubo CRT - *Cathode Ray Tube* -  com 
resolução de 640×480 pixels (figura 3) e uma taxa de atualização de 60Hz.

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

Estes parâmetros são calculados utilizando a resolução e taxa de atualização dos monitores. Os cálculos para a definição dos valores utilizados no projeto estão disponíveis na
[seção III.C deste arquivo](https://drive.google.com/file/d/1MlIlpB9TSnoPGEMkocr36EH9-CFz8psO/view). As especificações de parâmetros para diferentes resoluções podem ser encontrados no 
[manual da placa](https://fpgacademy.org/index.html)

</details>

<details>
<summary><b>Saída VGA na Placa</b></summary>

### Saída VGA na Placa
Na placa DE1-SoC, os sinais de sincronização são gerados diretamente pela Cyclone V SoC FPGA, com a conversão digital-analógica sendo feita por meio de Analog Devices ADV7123 para a 
representação das 3 cores RGB. Cada canal de cor RGB é representado por 8 bits e os sinais *hsync* e *vsync* são representados por 1 bit cada.
 

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

<blockquote>

**NOTE**
Os sinais de geração de vídeo e de cores são controlados pelo *Controlador VGA* implementado pelo processador CoLenda.
</blockquote>
</details>	

## Processador gráfico

O processador gráfico CoLenda foi desenvolvida pelo discente Gabriel Sá Barreto Alves como parte 
do seu trabalho de conclusão de curso (TCC) na Universidade Estadual de Feira de Santana (UEFS). O dispositivo gráfico permite o controle de polígonos convexos (triângulos e quadrados) 
e sprites em um monitor VGA com resolução de 640x480 pixels. No projeto desenvolvido para o TCC, o NIOS II foi utilizado como unidade de processamento principal.

> [!NOTE]
> No presente projeto, o NIOS II foi substituído pelo HPS da placa DE1-SoC.

Além do controle de polígonos e sprites, a GPU CoLenda permite alterar a cor de fundo do monitor, alterar blocos de fundo de dimensão 8x8 e criar sprites próprios.

<details>
	<summary><b>Instruções</b></summary>

### Instruções
Para realizar as atividades especificadas anteriormente, a GPU disponibiliza um conjunto de instruções, cada uma com tamanho e campos diferentes. A tabela abaixo lista as instruções 
disponíveis, assim como suas funções.  
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

A comunicação com o processador gráfico dá-se por meio dos barramentos de dados data A e data B (figura 6). O barramento data A é utilizado para transmissão dos dados de acesso à 
memória e registradores e dos códigos de operações. Já o data B é utilizado para transmissão dos demais dados customizáveis tais como cores e posição. Além disso, o dispositivo 
apresenta os seguintes sinais de controle:
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
aplicação de usuário, o módulo kernel e o hardware é esquematizado na figura 7. O fluxo inicia-se com a aplicação do
usuário que, por meio dos recursos disponibilizados pela biblioteca CoLenda, gerencia os dados
dos elementos a serem exibidos no monitor VGA e as chamadas das respectivas funções da *lib* para as exibições na tela.

Por sua vez, a biblioteca atua como uma mediadora entre a aplicação de usuário e o driver CoLenda, gerenciando as chamadas de sistema
necessárias, assim como as conversões das solicitações recebidas para o stream de caracteres a ser passado ao driver.
Por fim, o driver gerencia os sinais de controle e o barramento de dados do hardware, a fim de enviar as instruções recebidas da biblioteca.

## Driver CoLenda

A implementação e compreensão do driver CoLenda como um módulo carregável mediante a demanda perpassa por alguns conceitos fundamentais, como a arquitetura do sistema operacional Linux, 
que serão explicitados a seguir.

### 📖 Background
<details>
<summary><b>Arquitetura do Sistema Operacional Linux</b></summary>

#### Arquitetura do Sistema Operacional Linux

Existem dois modos de operação referentes ao modo de execução do processador: modo núcleo (ou modo kernel) e modo usuário. O kernel é parte do sistema operacional que tem acesso 
completo a todo o hardware e recursos, podendo executar qualquer instrução disponível na máquina. Portanto, o modo kernel possui privilégios de acesso e execução de subsistemas. Já o 
modo usuário possui  limitações e menos privilégios. 

A figura 8 exibe uma típica arquitetura do sistema operacional linux, onde o espaço kernel intermedia o acesso e o compartilhamento dos recursos de hardware, de maneira segura e justa, 
entre múltiplas aplicações. A janela de interação entre o espaço de usuário e do kernel se dá através de uma interface de chamadas de sistema em que, em mais alto nível, o kernel prove 
"serviços" às aplicações. Além do kernel, responsável pelo gerenciamento de processos, segurança, gerenciamento de memória e demais atribuições do sistema operacional, os drivers de 
dispositivos também compõem o espaço do kernel. 
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
</details>


<details>
<summary><b>Mapeamento de Memória</b></summary>

#### Mapeamento de Memória

Para acessar endereços físicos de memória nos modos de usuário e kernel, faz-se necessária a virtualização destes endereços.
<div align="center">
  <figure>  
    <img src="docs/images/memory-mapping.png" width="800">
    <figcaption>
      <p align="center"><b>Figura 9 - </b>Mapeamento de memória via MMU</p>
    </figcaption>
  </figure>
</div>

A memória virtual é uma técnica utilizada para gerenciamento de memória nos computadores. Nela, cada programa possui seu próprio espaço de endereçamento o qual é mapeado na memória 
física. Quando o programa referencia uma parte do espaço de endereçamento que está na memória física, o hardware encarrega-se de realizar rapidamente o mapeamento (figura 9). 
Nos módulos kernel, as funções [`ioremap()` e `iounmap()`](https://www.oreilly.com/library/view/linux-device-drivers/0596000081/ch08s04.html) são utilizadas. Já nas aplicações de 
usuários, as funções [`mmap` e `unmap`](https://www.man7.org/linux/man-pages/man2/mmap.2.html) A partir do endereço virtual gerado, pode-se realizar as devidas manipulações.

</details>

<details>
<summary><b>Driver do Dispositivo</b></summary>

#### Driver de dispositivo
O <i>driver</i> é uma abstração para acesso a um dispositivo de hardware que permite uma infraestrutura de interação com o aparato físico. Apesar da possibilidade de drivers sendo 
executados no espaço de usuário, eles são geralmente executados no espaço do kernel como módulo kernel, que podem ser carregados e descarregados em tempo de excução.

Em sistemas UNIX, dispositivos de hardware são acessados pelo usuário através da sua abstração em arquivos especiais, que estão associados ao correspondente driver e hardware como 
representa na figura 10. Esse arquivos estão disponíveis e agrupados no diretório <code>/dev</code> e cada chamada de sistem como `open`, `read`, `write` etc. é redirecionada pelo 
sistema operacional para driver que faz o gerenciamento do dispositivo físico.

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

Nas distribuições UNIX, os drivers de dispositivos e seus arquivos podem ser do tipo *caractere* ou *bloco*. A principal diferença entre eles se dá pelo fato dos drivers de caracteres 
manipularem uma pequena quantidade de dados, geralmente strings de bytes, para dispositivos como mouse, teclado e portas seriais. Já o segundo tipo, acessa e transfere um grande volume 
de dados organizados em blocos, além de necessitarem de buffering. A exemplo tem-se drivers para disco rígido, memória RAM, etc. Desse modo, o driver CoLenda para comunicação com o 
processador gráfico é do tipo caractere.

Além disso, os dispositivos tem uma identificação característica composta pelo *major* e *minor number*. O *major number* identifica o tipo do dispositivo e o *minor* cada dispositivo 
físico associado ao driver. Ou seja, caso existam vários dispositivos do mesmo tipo eles terão o mesmo *major number*, porém *minors* diferentes para cada um deles.

Dessa maneira, ao acessar o arquivo especial do dispositivo, uma chamada de sistema é realizada e o driver associado realiza a operação de leitura ou escrita de dados no equipamento 
físico, como é representado na figura 11.

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
</details>

### Driver desenvolvido
O módulo kernel CoLenda é um driver de caractere que realiza a comunicação com o processador gráfico. Este módulo implementa as funções *open*, *release*, *write*, além das funções 
*init* e *exit*.

As funções *open* e *close* apenas indicam no log do sistema que o driver foi aberto e liberado, respectivamente. Por sua vez, a função *write* recebe a instrução da GPU da aplicação de 
usuário, realiza a separação deste stream de bits entre os barramentos *dataA* e *dataB* e envia o sinal de escrita na a fila de instruções do peocessador gráfico. 
Devido aos tempos de sincronização do padrão VGA e do tamanho fixo da fila de instruções da GPU, os sinais de finalização da renderização de uma tela (*screen*) e de fila cheia são 
checados (*wrfull*), a instrução passada ao driver só é escrita caso a renderização tenha terminado e a fila não esteja cheia. Caso contrário, um erro é retornado.

Para o gerenciamento dos sinais de controle (reset_pulsecounter, screen, wr_reg e wr_full) e dos barramentos de dados (dataA e dataB) do processador gráfico, o driver implementa a 
virtualização destes endereços físicos. 
Como apresentado na figura 6, o processador gráfico recebe os sinais *dataA*, *dataB*, *wrreg*, *reset_pulsecounter* bem como envia os sinais *screen* e *wrfull*, cujos endereços base 
dos barramentos da GPU são respectivamente 0x80, 0x70, 0xc0, 0x90, 0xa0 e 0xb0. O gerenciamento destes sinais é realizado por meio da virtualização destes endereços físicos. Para a 
criação e utilização do mapeamento de memória são manipuladas a ponte `ALT_LWFPGASLVS_OFST` (0xFF200000)(Lightweight HPS-to-FPGA Bridge), encarregada da conexão entre o FPGA e o HPS da 
placa, juntamente com a `HW_REGS_BASE` (0xFC000000), que armazena o endereço base para os registradores de acesso aos periféricos do HPS e a `HW_REGS_SPAN` (0x04000000), encarregada do 
armazenamento em bytes da região de memória a ser mapeada. 

## Biblioteca CoLenda

A biblioteca desenvolvida provê uma abstração da comunicação com o driver de dispositivo, facilitando a interação do usuário com o 
módulo kernel do hardware. Esta *lib* disponibiliza constantes para a seleção de sprites, estruturas para a organização dos elementos a
serem exibidos, funções respectivas às instruções do processador gráfico, funções de pseudo-instruções, que executam conjuntos de instruções, e funções internas auxiliares.
> [!NOTE]
> Os sprites disponíveis para seleção estão salvos em hardware no processador gráfico.
> Nenhum deles foi criado pela biblioteca

<details >
<summary><b>Constantes de sprite</b></summary>

### Constantes de sprite
As constantes de sprite implementadas visam facilitar seleção, pois nomeiam os sprites disponíveis e abstraem o número relacionado ao endereço de localização dos mesmos (*offset*). A 
figura 12 ilustra os sprites diponibilizados na GPU e a tabela abaixo lista a relação entre os sprites e os valores associados.

<div align="center">

|   Define    | Valor| Sprite associado
|:-----------:|:----:|:-------------------:|
| ORANGE_BLOCK| 0    | Bloco laranja
|  BLUE_BLOCK | 1    | Bloco azul
|  MEDAL			| 2		 | Medalha
|  BOMB 			| 3	   | Bomba
|  TREE	  		| 4    | Árvore
| SHIP_UP 		| 5    | Nave virada para cima
| SHIP_RIGTH 	| 6    | Nave virada para direita
| SHIP_DOWN		| 7	   | Nave virada para baixo
| SHIP_LEFT		| 8    | Nave virada para esquerda
| COIN	   		| 9		 | Moeda
| DIAMOND		  | 10	 | Diamante
| LASER_VERTICAL| 11 | Laser na vertical
| LASER_DIAGONAL1| 12| Laser na diagonal principal
| LASER_HORIZONTAL|13| Laser na horizontal
| LASER_DIAGONAL2| 14| Laser na diagonal secundária
| HEART		  	| 15   | Coração azul
| LOG			    | 16   | Tronco de arvore
| BLUE_CAR		| 17   | Carro de corrida azul
| GREEN_CAR		| 18   | Carro de corrida verde
| PURPLE_CAR	| 19   | Carro de corrida roxo
| YELLOW_CAR	| 20   | Carro de corrida amarelo
| ALIEN1		  | 21   | Alien do space invaders
| ALIEN2  		| 22	 | Alien do space invaders
| DRAGON		  | 23	 | Pedra
| CUP		    	| 24   | Troféu

</div>
<div align="center">
  <figure>  
  <img src="docs/images/sprites.png">
  <figcaption>
  <p align="center">
  
  [**Figura 12** - Sprites disponíveis na GPU CoLenda](https://drive.google.com/file/d/1rCixSRIddlwt_PSXwhSkDDXlJrNQqvs_/view)
  
  </p>
  </figcaption>
  </figure>
</div>

</details>

<details>
<summary><b>Structs</b></summary>

### Structs
As structs implementadas visam facilitar a organização das informações dos elementos a serem (ou sendo) exibidos no monitor VGA. A tabela abaixo lista as structs implementadas, assim 
como sua breve descrição e seus atributos.

| Struct      | Descrição     |  Atributos    |
|    :----:   | :-----------: | :-----------: |
|  Cor        | Define os campos que uma cor deve possuir. Utilizada nas demais estruturas que necessitam de um campo de cor| Vermelho, verde e azul |
|  Sprite     | Define os dados necessários para a exibição de um sprite        | Coordenadas x e y, offset (para a escolha do sprite), registrador (espaço de memória que será ocupado) e visibilidade |
| Bloco de background   | Agrupa as informações necessárias para a edição de um bloco de blockground | Cor (struct) e coordenadas x e y  |
| Pixel   | Define as informações necessárias para a criação de um pixel de um sprite. Localizado na memória de sprites      | Endereço de memória e cor (struct) |
| Polígono   | Agrupa as informações necessárias para a exibição de um polígono   | Coordenadas x e y, camada, tamanho, forma (triângulo ou quadrado e cor (struct) |


<blockquote>

**WARNING**

As coordenadas de sprites são relativas à disposição dos pixels na tela (640x480). Já as coordenadas dos blocos de blackground são relativas à disposição dos blocos de tamanho 8x8 
pixels (totalizando 80x60 blocos). Cada bloco possui um endereço na memória.
</blockquote>

</details>

<details >
<summary ><b>Funções correspondentes às instruções</b></summary>

### Funções correspondentes às instruções
Estas funções, por representarem indiretamente as instruções do processador, são utilizadas pela aplicação de usuário para controlar a exibição dos elementos no monitor VGA. Dessa 
forma, cada função encarrega-se de um elemento. A tabela lista as funções deste tipo, bem como os arqumentos recebidos e a instrução da GPU relacionada com as mesmas.
<div align="center">
	
|      Função          |          Argumento         | Instrução relacionada |
|     -----------      |        -----------         |           ----        |
|   Setar pixel        |         Struct pixel       |           WSM         |
|  Setar cor de fundo  |         Struct cor         |           WRB         |
| Setar bloco de fundo | Struct bloco de background |           WSM         |
|    Setar sprite      |       Struct sprite        |           WRB         |
|    Setar polígono    |      Struct polígono       |           DP          |

</div>
</details>

<details>
<summary ><b>Funções de pseudo-instruções</b></summary>
	
### Funções de pseudo-instruções 
Como dito anteriormente, as funções de pseudo-instruções realizam uma determinada atividade a partir da execução de um bloco de instruções da GPU. Estas facilitam o desenvolvimento de 
imagens por meio da GPU. As pseudo-instruções implemetadas são: desenhar uma linha vertical, desenhar uma linha horizontal, desenhar um bloco de background e limpar tela. A tabela 
abaixo lista as pseud instruções juntamente com suas descrições e seus argumentos.

| Função | Descrição | Argumento |
|  :-----------:  | :-----------: | :-----------: |
| Desenhar linha vertical | Desenha uma linha vertical utilizando blocos de background. Chama a função setar bloco de background n vezes alterando apenas a coordenada y | Coordenadas iniciais x e y, tamanho (n) e  cor (struct)|
| Desenhar linha horizontal | Desenha uma linha horizontal utilizando blocos de background. Chama a função setar bloco de background n vezes alterando apenas a coordenada x | Coordenadas iniciais x e y, tamanho (n) e  cor (struct)|
| Desenhar bloco de background | Seta um bloco de background. Dispensa a instância da struct| Coordenadas iniciais x e y, e cor (struct)|
| Clear | Reseta a tela| - |

</details>

<details >
<summary><b>Funções internas  auxiliares</b></summary>

### Funções internas auxiliares
Estas funções são utilizadas pela biblioteca na geração dos streams de caracteres e nas chamadas de write. São elas:

- função para escrever no buffer do driver as instruções: gerencia a chamada de sistema write
- função para transformar 2 wchar_t em uma string de 8 *char*

</details>

<details >
<summary ><b>Validação de valores e tratamento de erros</b></summary>

###  Validação de valores e tratamento de erros

A biblioteca apresenta recursos para validação dos valores atribuídos pelo usuário aos argumentos das structs, tais como tamanho dos canais de cores, valor das coordenadas x e y dos 
blocos de background e dos polígonos. Estas checagens foram implementadas devido a limitação de exibição no monitor VGA devido ao tamanho fixo dos compos das intruções do processador 
gráfico. A detecção de um erro retorna um valor de erro à aplicação do usuário  e exibe no terminal o erro uma mensagem referente ao erro ocorrido

</details>	

## Exemplo de utilização
Apesar do número limitado de elementos disponibilizados pelo processador gráfico, uma vasta gama de imagens podem ser renderizadas. Um exemplo de imagem que pode ser criada
é mostrada na figura 13 na qual foram utilizados todos os recursos do hardware:
- polígonos: usados para desenhar os botões direitos do gameboy
- cor de background: definido para branco
- blocos de background: usados para desenhar o corpo, a tela e os botões esquerdos do gameboy
- sprites: usados para criar o cenário na tela do gameboy

As pseudo instruções foram todas utilizadas para facilitar o desenvolvimento da imagem. O código para a renderização da imagem encontra-se [aqui](source/Lib/gameboy_example.c).

<div align="center">
  <figure>  
    <img src="docs/images/gameboy.jpg" height="500px">
    <figcaption>
      <p align="center"><b>Figura 13</b> - Imagem do gameboy exibida no monitor VGA</p>
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
<summary><b>Setando background</b></summary>

### Setando background
Neste primeiro caso, buscou-se testar a definição da cor de fundo do monitor. Para isso, utilizou-se um aplicação de usuário para criar uma struct *color_t*  com os valores RGB 0, 7 e 
0, respectivamente, e realizar a chamada das funções *GPU_open*, *set_background_color* e *GPU_close*, nesta ordem,da biblioteca CoLenda. Como resultado, esperava-se que a cor de fundo 
do monitor VGA fosse alterada para verde.

Como pode-se observar na figura 14, a cor de fundo exibida no monitor após a execução do programa condiz com o resultado esperado.

<div align="center">
  <figure>  
    <img src="docs/images/background-test.jpg" height=500>
    <figcaption>
      <p align="center"><b>Figura 13</b> - Resultado do teste de background</p>
    </figcaption>
  </figure>
</div>

</details>

<details>
<summary><b>Setando polígonos</b></summary>

### Setando polígonos
Neste caso de teste, buscou-se testar a exibição de polígonos. Para isso, utilizou-se um aplicação de usuário para criar uma struct *color_t* com os valores RGB 7, 0 e 0, 
respectivamente, e a struct *polygon_t* `red_square = {512,240,0,0,1,red}`. Em seguida realizou-se a chamada das funções *GPU_open*, *set_polygon* e *GPU_close*, nesta ordem, da 
biblioteca CoLenda. Como resultado, esperava-se que um quadrado vermelho 20x20 fosse exibido no centro do monitor VGA.

Como pode-se observar na figura 15, o polígono exibido no monitor após a execução do programa condiz com o resultado esperado.

<div align="center">
  <figure>  
    <img src="docs/images/quadrado-teste.jpg" height=500>
    <figcaption>
      <p align="center"><b>Figura 15</b> - Resultado do teste de polígono (quadrado)</p>
    </figcaption>
  </figure>
</div>

O teste foi repetido com a struct `black_triangle = {512,240,0,1,1,black}`, onde *black* é uma struct *color_t* com os valores RGB iguais a 7,7 e 7, respectivamente. Esperava-se que um 
triângulo preto 20x20 fosse exibido no centro do monitor VGA. Como pode-se observar na figura 16, o polígono exibido no monitor após a execução do programa condiz com o resultado 
esperado.  
<div align="center">
  <figure>  
    <img src="docs/images/triangulo-teste.jpg" height=500>
    <figcaption>
      <p align="center"><b>Figura 16</b> - Resultado do teste de polígono (triangulo)</p>
    </figcaption>
  </figure>
</div>

</details>

<details>
<summary><b>Teste de sobreposição de polígonos</b></summary>

### Teste de sobreposição de polígonos
Neste caso de teste, buscou-se testar a sobreposição de polígonos. Para isso, utilizou-se um aplicação de usuário as structs do tipo *polygon_t* `red_square = {512,240,0,0,1,red}` e 
`black_triangle = {512,240,1,1,1,black}`. Em seguida realizou-se a chamada das funções *GPU_open*, *set_polygon* (uma para cada polígono) e *GPU_close*, nesta ordem, da biblioteca 
CoLenda. Como resultado, esperava-se que um quadrado vermelho 20x20 fosse exibido no centro do monitor VGA e um triângulo preto 20x20 fosse exibido no centro também no centro da tela e 
sobre o quadrado.

Como pode-se observar na figura 17, a ordem de exibição dos polígonos no monitor após a execução do programa condiz com o resultado esperado.  
<div align="center">
  <figure>  
    <img src="docs/images/sobreposicao-teste.jpg" height=500>
    <figcaption>
      <p align="center"><b>Figura 16</b> - Resultado do teste de sobreposição de polígonos</p>
    </figcaption>
  </figure>
</div>
</details>

<details>
	<summary><b>Teste de limite máximo de posição de polígonos</b></summary>

### Teste limite máximo de posição de polígonos
Neste caso, o trecho de código abaixo foi utilizado e, como resultado, espera-se que a cor de fundo fosse definida para branco e um
triângulo preto de tamanho 20x20 fosse exibido na posição (511, 240). Como observa-se na figura 17, os devidos elementos foram setados com as configurações corretas. 

Este triângulo ocupa a posição limite no eixo x que os polígonos podem ocupar devido ao tamanho do campo coordenada x da instrução DP (9 bits). Caso um valor maior que 511 seja passado para a GPU, o polígono não é exibido. Por isso, a biblioteca realiza a verificação deste argumento e retorna um erro para os valores fora do range.  

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
      <p align="center"><b>Figura 19</b> - Teste de posição limite de polígonos no eixo x</p>
    </figcaption>
  </figure>
</div>
</details>

<details>
<summary><b>Teste de limite mínimo de posição de polígonos</b></summary>

### Teste de limite mínimo de posição de polígonos
Neste caso, o mesmo trecho de código da seção anterior foi utilizado  alterando-se apenas as coordenas x e y do polígono. Como resultado, esperava-se que a cor de fundo fosse definida 
para branco e um triângulo preto de tamanho 20x20 fosse exibido na posição 
(10, 10). Como observa-se na figura 20, o 
triângulo não foi setado corretamente. O teste foi repetido com o quadrado e o erro persistiu (figura 21). 

Após diversas análises e múltiplos testes, concluiu-se que o erro pertence à GPU. Todos os polígonos cujas coordenadas x e/ou y sejam menores que metade do tamanho do polígono não são 
exibidos ou sua exibição assume um tamanho aleatório devido a erros nos cálculos. Devido a isso, a biblioteca realiza a verificação destes campos e retorna um erro para os valores fora 
do _range_.

<div align="center">
  <figure>  
    <img src="docs/images/triangulo_bug.jpg" height="500px">
    <figcaption>
      <p align="center"><b>Figura 20</b> - Resultado do teste com triângulo no monitor</p>
    </figcaption>
  </figure>
</div>

<div align="center">
  <figure>  
    <img src="docs/images/quadrado_bug.jpg" height="500px">
    <figcaption>
      <p align="center"><b>Figura 21</b> - Resultado do teste com quadrado no monitor</p>
    </figcaption>
  </figure>
</div>
	
</details>


<details>
<summary><b>Teste com blocos de background</b></summary>

### Teste com blocos de background
Neste caso, o trecho de código abaixo foi utilizado para testar os limites de representação dos blocos de background. Como resultado, esperava-se que um erro ocorresse,  o que não 
aconteceu.
Novos testes foram repetidos e, a partir disto, concluiu-se que o endereçamento dos blocos de background contém 13 bits, ao invés dos 12 especificados no TCC. Na figura 22, estão 
destacados todos os blocos de background que não seriam abrangidos caso o endereçamento tivesse 12 bits.

> [!NOTE]
> Devido a esta descoberta, a bibloteca CoLenda foi alterada para aceitar valores de endereçamento de blocos de background referente aos 13 bits.

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
      <p align="center"><b>Figura 22</b> - Resultado do teste dos limites de representação dos blocos de background no monitor</p>
    </figcaption>
  </figure>
</div>
</details>

<details>
<summary><b>Teste com a função <i>clear</i></b></summary>

### Teste com *clear*
Neste caso, buscou-se testar a função *clear* responsável pela limpeza da tela. Para isto, setou-se o background do monitor VGA para a cor branca e exibiu-se um sprite no centro da 
tela. Em seguida, realizou-se a chamada da função *clear*. Como resultado, esperava-se que todos os elementos exibidos na tela fosse "apagados" e a cor de fundo fosse setada para preto. 

Como observa-se na figura 23, todos os elementos foram removidos da tela e a cor de background foi definida para preto.

<div align="center">
  <figure>  
    <img src="docs/images/clear.gif">
    <figcaption>
      <p align="center"><b>Figura 23</b> - Teste com <i>clear</i></p>
    </figcaption>
  </figure>
</div>
</details>

</details>

Durante os testes, o possível problema da fila de instruções cheia foi tratado por meio de um delay a cada 12 instruções na biblioteca, garantindo que os comanandos sejam acessados pela 
GPU na janela de tempo após a renderização da tela.

Além de compreender as políticas de gerenciamento de sistema operacional Linux em arquitetura ARM e utilizar a interface de conexão entre HPS e FPGA da DE1-SoC, este projeto proporcionou o aprofundamento e prática em uma distribuição Linux embarcada e dos conceitos de interação entre hardware e software.

Assim sendo, o driver e a biblioteca atenderam aos objetivos nas variadas situações verificadas. Portanto, o produto desempenha de maneira satisfatória a intercomunicação usuário-driver-harware.

## Contribuindo
Todas as contribuições são bem-vindas, sejam elas para o código ou para a documentação. Para isso, utilize a formatação e as versões adotadas no projeto, realize os testes necessários para manter a integração, bem como adote _pull requests_ para cada modificação.

## Referências

ALVES, Gabriel - [Desenvolvimento de uma Arquitetura Baseada em Sprites para criacão de Jogos 2D em Ambientes reconfiguraveis utilizando dispositivos FPGA.](https://drive.google.com/file/d/1MlIlpB9TSnoPGEMkocr36EH9-CFz8psO/view) Orientador: DIAS, Afranserai, SARINHO, Vitor. 2024. Trabalho de Conclusão de Curso - Engenharia da Computação, UEFS, Feira de Santana. Acessado em: 14 maio. 2024. 

[Character device drivers — The Linux Kernel documentation.](https://linux-kernel-labs.github.io/refs/heads/master/labs/device_drivers.html) 

[Introduction — The Linux Kernel documentation](https://linux-kernel-labs.github.io/refs/heads/master/lectures/intro.html)

TANENBAUM, A. S.; BOS, Herbert. Sistemas operacionais modernos. 4. ed. São Paulo: Pearson Education do Brasil, 2016. Acesso em: 30 maio. 2024.

[History and Evolution of GPU Architecture](https://www.igi-global.com/chapter/history-and-evolution-of-gpu-architecture/139841)

[GPU computing](https://escholarship.org/content/qt0cv1p1nc/qt0cv1p1nc_noSplash_e93469c5acbe804c7c045217eee807bb.pdf)

[Understanding the structure of a Linux Kernel Device Driver por Seegio Prado](https://youtu.be/XoYkHUnmpQo?si=oNfgFA-yZhhQlsQd)

[Let's code a Linux Driver por 4GNU_Linux](https://youtube.com/playlist?list=PLCGpd0Do5-I3b5TtyqeF1UdyD4C-S-dMa&si=HYJ-_VlVx9gj2VPw)

[Chapter 3 Char devices - O'Reilly](https://www.oreilly.com/library/view/linux-device-drivers/0596005903/ch03.html)
