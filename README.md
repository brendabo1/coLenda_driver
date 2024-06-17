<h1 align="center"><i>Driver CoLenda</i></h1>

<h3 align="center">Um módulo de kernel Linux para a comunicação com o dispositivo gráfico CoLenda</h3>
<h4 align="center">
<a href="https://github.com/camilaqPereira/coLenda_driver/commits/main/"> <img alt="coLenda_driver commits" src="https://img.shields.io/github/last-commit/camilaqPereira/coLenda_driver/main"></a>
<a href="https://github.com/camilaqPereira/coLenda_driver/commits/main/"> <img alt="coLenda_Driver commits" src="https://img.shields.io/github/commit-activity/t/camilaqPereira/coLenda_driver">
</a>
<a href="https://github.com/camilaqPereira/coLenda_driver"><img alt="coLenda_driver repo" src="https://img.shields.io/github/created-at/camilaqPereira/coLenda_driver">
</a>

</h4>

<div align="center">
	
[Sobre o projeto](README.md#sobre-o-projeto) • [Instalação](README.md#instalação) • [Solução geral](README.md#solução-geral) • [Driver](README.md#driver-colenda-1) • [Lib](README.md#biblioteca-colenda) • [Testes](README.md#produto-e-testes-realizados)
	

</div>

## Sobre o projeto

<details>
<summary> <h3 style="font-weight: bold">Requisitos</h3></summary>
A solução deve atender às condições e aos requisitos predeterminados, de modo que:
- o código deve ser escrito na linguagem C
- a biblioteca deve conter, no mínimo, uma função para cada instrução do processador gráfico
- a biblioteca deve seguir as recomendações descritas em [C coding style por Tilen Majerle](https://github.com/MaJerle/c-code-style)

</details>

## Contribuidores

<a href="https://github.com/brendabo1"><img src="https://avatars.githubusercontent.com/u/69097241?v=4" title="brendabo1" width="50" height="50"></a>
<a href="https://github.com/camilaqPereira"><img src="https://avatars.githubusercontent.com/u/116687830?v=4" title="camilaqPereira" width="50" height="50"></a>
<a href="https://github.com/DestinyWolf"><img src="https://avatars.githubusercontent.com/u/64764136?v=4" title="DestinyWolf" width="50" height="50"></a>


## Instalação
<details>
<summary><h3 style="fot-weight:bold">Requisitos</h3></summary>

- Possuir conexão com internet;
- Possuir o compilador gcc;
- Possuir o git instalado;
- Utilizar uma placa de desenvolvimento FPGA DE1-SoC;
- Possuir o processador gráfico CoLenda na FPGA
- Possuir um monitor conectado à placa por meio da saída VGA

</details>

### 1. Clonar o repositório
Abra o terminal do seu dispositivo e execute o seguinte comando:
```
git clone https://github.com/camilaqPereira/coLenda_driver.git
```
### 2.Acessar a pasta */source/driver* e compilar o driver
Para acessar a pasta */source/driver* e compilar o módulo kernel, basta executar os seguintes comandos:
```
cd /source/driver
make all
```
### 3. Executar o script de carregamento do driver
Execute o comando:
```
sudo ...
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
      <p align="center"><b>Figura 1</b> - Kit de Desenvolvimento DE1-SoC</p>
      <p align="center">Fonte: Terasic Technologies</p>
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
      <p align="center"><b>Figura 2</b> - Diagrama de Blocos da DE1-SoC</p>
      <p align="center">Fonte: FPGAcademy.org</p>
    </figcaption>
  </figure>
</div>

O diagrama de blocos do sistema computacional, apresentado na figura 2,  explicita os componentes do Cyclone® V da Intel®, bem como suas conexões. O HPS inclui um processador ARM® Cortex-A9 MPCore™ de 2 núcleos com uma distribuição Linux embarcada destinada a processamentos de propósito geral,  além da memória DDR3 e dos dispositivos periféricos. Já a FPGA possibilita uma variedade de implementações através da programação dos blocos lógicos.


> A comunicação bidirecional entre a o HPS e a FPGA se dá por meio das *FPGA bridges*. 
> No sentido HPS-FPGA, todos os dispositivos de entrada e saída (E/S) conectados à FPGA são acessíveis ao processador através do mapeamento de memória.
> As informações sobre o endereçamento dos periféricos estão disponíveis na [documentação da placa](https://fpgacademy.org/index.html).

</details>

## Processador gráfico
## Solução geral
O produto desenvolvido implementa a intercomunicação entre o software e o dispositivo gráfico CoLenda. O fluxo de comunicação entre a aplicação de usuário, o módulo kernel e o harware é esquematizado na figura 3.
<div align="center">
  <figure>  
    <img src="docs/images/solucao_geral.png"">
    <figcaption>
      <p align="center"><b>Figura 3</b> - Esquema em blocos da solução geral </p>
      <p align="center">Fonte:Elaboração própria</p>
    </figcaption>
  </figure>
</div>

A aplicação do usuário instancia as estruturas disponibilizadas pela biblioteca CoLenda, assim como realiza a chamada das funções disponíveis. Por sua vez, a biblioteca gerencia as chamadas de sistema necessárias durante a comunicação com o driver e converte as solicitações do usuário em um formato compreensivel pelo driver. Por fim, o driver comunica-se diretamente com barramento de dados do hardware.
## Driver CoLenda
## Biblioteca CoLenda
A biblioteca desenvolvida facilita a interação do usuário com o driver do dispositivo gráfico, dispondo de estruturas e funções que provem uma abstração para o uso da GPU.

<details>
<summary><b>Structs</b></summary>

### Structs

A biblioteca disponibiliza diversas estruturas a fim de organizar os dados de maneira a facilitar o uso das funções pelo usuário, assim como facilitar a implementação das funções que enviam esses dados para a escrita na GPU. A tabela abaixo lista estas structs, bem como suas finalidades específicas e atributos

| Struct      | Descrição | Atributos |
| ---- | ----------- | ----------- |
| Cor      | Define os campos que uma cor deve possuir. Utilizada nas demais estruturas que necessitam de um campo de cor| Vermelho, verde e azul |
| Sprite   | Define as informações de um sprite        | Coordenadas x e y, offset (para a escolha do sprite), registrador (espaço de memória que será ocupado) e visibilidade |
| Bloco de background   | Agrupa as informações de um bloco de blockground | Cor (struct) e coordenadas x e y  |
| Pixel   | Define as informações necessarias para a criação de um pixel de um sprite. Localizados na memória de sprites      | Endereço de memória e cor (struct) |
| Polígono   | Organiza as informações de um polígono   | Coordenadas x e y, camada, tamanho, forma (triângulo ou quadrado e cr (struct) |


> COORDENADAS DE SPRITES vs COORDENADAS DE BLOCOS DE BACKGROUND
> As coordenadas de sprites são relativs a disposição dos pixels na tela (640x480).
> Já as coordenadas dos blocos de blackground são relativas à disposião dos blocos de tamanho 8x8 (totalizand 80x60 blocos).

</details>
</p>
Utilizando da função write do char drive da GPU foi possível implementar as seguintes funções:
<ul>
	<li>escrita ou alteração de um pixel na memória de sprite</li>
	<li>alteração da cor do fundo da tela</li>
	<li>alteração de um bloco do fundo</li>
	<li>inserção de um sprite na tela</li>
	<li>inserção de um poligno na tela</li>
</ul>

Escrita ou alteração de um pixel na memória de sprites: 
Essa função foi implementada através da função assembly WSM que esta inserida na gpu, a mesma possibilita alterar os pixeis dentro da memória de sprite, onde cada instrução possui os seguintes campos
(imagem dos campos da função WSM)

Na biblioteca foi implementada uma função que recebe uma struct pixel, que contem um endereço e um struct cor referente ao endereço do e nova cor do pixel respectivamente assim dispensando a necessidade do programador entender os campos da instrução e enviar apenas o que ele deseja que seja feito, respeitando claro os limites da gpu situados a cima

Alteração da cor de fundo:
Essa função foi implementada utilizando a instrução WRB onde em uma das suas variantes é possível ser utilizada para alterar a cor do fundo

(imagem da função WRB com os campos para alterar a cor de fundo)

Na biblioteca a função exige que o usuário informe apenas a cor que deseja colocar e o codigo se encarrega de enviar para a gpu o registrador responsável por guarda a cor do fundo.

Alteração de um bloco do fundo:
Essa função se utiliza da instrução WSM responsável por alterar ou desabilitar um bloco do fundo do background
O background é dividido em blocos de 8 por 8 pixeis, assim gerando uma tela de 80x60 blocos, onde cada bloco possui um endereço na memória de background.
A instrução WSM possui os seguintes campos
(criar uma imagem pra instrução wsm e por aqui)

Usando a biblioteca é necessário apenas informa a coordenada x e y do bloco, além da cor que o bloco tera e a própria função se encarrega de calcular o endereço do bloco e fazer a chamada do método write para o driver, dispensando a necessidade do programador realizar o calculo manual de qual o endereço do bloco e ter que entender quais os campos da instrução.

Inserção de um sprite na tela:
A gpu CoLenda possui alguns sprites pré-renderizados em sua memória de sprites, assim possibilitando o uso mais eficaz dos recursos, desse modo é possível imprimir um sprite que está na memória na tela.
A instrução WRB também é utilizada para desenhar sprites na tela, nessa variação ela possui os seguintes campos

(campos da instrução WRB no formato de settar sprites);

A função desenvolvida na biblioteca solicita do usuário apenas uma struct do sprite que o mesmo deseja renderizar, facilitando a manipulação desse sprite além de facilitar e simplificar o código do programador, a biblioteca se encarrega de ler as informações, separar os campos e realizar o envio para o driver.


Inserção de um polígono na tela:
Para desenhar um polígono na tela a gpu conta com uma instrução chamada DP, que tem como único objetivo desenhar quadrados e triângulos na tela e os armazenar na memória de polígonos. Os campos da instrução DP estão informados abaixo

(imagem da instrução DP)

Na biblioteca a função de inserir polígonos recebe como parâmetro apenas uma strutura polígono e faz a identificação dos campos e os devidos deslocamentos para possibilitar seu envio e bom funcionamento no driver

Além dessas funções foram inseridas algumas pseudo instruções que facilitam o desenvolvimento de aplicações para a gpu

	1 → desenhar uma linha na vertical usando blocos do background
	2 → desenhar uma linha horizontal usando blocos do background
	3 → desenhar um bloco sem a necessidade de instanciar uma estrutura;

A função de desenhar uma linha na vertical implementa por baixo dos panos a função de alterar um bloco do fundo porém faz várias chamadas a mesma função alterando apenas a coordenada do eixo y.
Para utilizar essa função o programador deve passar a coordenada inicial x e y, a cor da linha e o tamanho dela. O fluxograma abaixo descreve o fluxo da instrução

(fluxograma da instrução de criar uma linha usando blocos de fundo)

A função de criar uma linha horizontal funciona semelhante a pseudo instrução de criar uma linha vertical com a diferença que dessa vez o eixo que sera incrementado é o eixo x. Os parâmetros são o tamanho da linha, a cor e a coordenada inicial x e y;

(fluxograma da instrução de criar uma linha usando blocos de fundo)

A pseudo instrução de criar um bloco do background surge para dispensar a criação e armazenamento de uma struct para alterar blocos do fundo, basta realizar a chamada da função 
	
Como o drive só aceita chat foram utilizadas variáveis do tipo achar_t que, em resumo, é tipo especial de chat que possui 32 bits nas distribuições Linux, além disso, foi implementada uma função chamada de wchar2char que converte os 2 achar em uma string de 8 char para possibilitar seu envio ao driver, cada char possui 8 bits totalizando os 64 necessários para o envio de cada instrução

Além disso a biblioteca ainda possui uma função que tem como única responsabilidade escrever no buffer do driver as instruções, abstraindo assim essa funcionalidade;



A biblioteca também implementou recursos para validação dos valores inseridos pelo usuário, pois como as instruções trabalhavam com tamanhos e valor distintos foi imprescindível a existência de recursos para validar essas informações. No momento que é detectado um valor que esta a cima do que é possível representar ou que é negativo, é realizada uma interrupção no algoritmo e um erro é retornado ao usuário, para o que o mesmo trate.

(mostrar os trechos de validação das informações)

Além disso, a biblioteca implementou algumas definições que visam facilitar a escolha do sprite, pois abstraem o número relacionado ao endereço que determinado sprite esta localizado.

(colocar os defines)

</p>

## Produto e testes realizados
## Conclusão
## Referências


