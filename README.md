<h1 align="center"><i>Driver CoLenda</i></h1>

<h3 align="center">Desenvolvimento de um <i>driver</i> para o dispositivo gráfico CoLenda</h3>


<details open>
<summary><h2>Sumário</h2></summary>

  - [Sobre o projeto](README.md#sobre-o-projeto)
  - [Softwares utilizados](README.md#softwares-utilizados)
  - [Kit de desenvolvimento DE1-SoC](README.md#kit-de-desenvolvimento-de1-soc)
  - [O processador gráfico](README.md#processador-gráfico)
  - [Solução geral](README.md#solução-geral)
  - [Driver CoLenda](README.md#driver-colenda-1)
  - [Biblioteca CoLenda](README.md#biblioteca-colenda)
  - [Produto e testes realizados](README.md#produto-e-testes-realizados)
  - [Conclusão](README.md#conclusão)
  - [Referências](README.md#referências)

</details>


## Contribuidores

<a href="https://github.com/brendabo1"><img src="https://avatars.githubusercontent.com/u/69097241?v=4" title="brendabo1" width="50" height="50"></a>
<a href="https://github.com/camilaqPereira"><img src="https://avatars.githubusercontent.com/u/116687830?v=4" title="camilaqPereira" width="50" height="50"></a>
<a href="https://github.com/DestinyWolf"><img src="https://avatars.githubusercontent.com/u/64764136?v=4" title="DestinyWolf" width="50" height="50"></a>

## Sobre o projeto

<details>
<summary> <h3 style="font-weight: bold">Requisitos</h3></summary>
A solução deve atender às condições e aos requisitos predeterminados, de modo que:
- o código deve ser escrito na linguagem C
- a biblioteca deve conter, no mínimo, uma função para cada instrução do processador gráfico
- a biblioteca deve seguir as recomendações descritas em [C coding style por Tilen Majerle](https://github.com/MaJerle/c-code-style)

</details>

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
## Processador gráfico
## Solução geral
## Driver CoLenda
## Biblioteca CoLenda
<p>
A biblioteca foi desenvolvida com a intenção de facilitar a interação do usuário com o driver do dispositivo gráfico, assim a biblioteca dispõem de estruturas e funções para facilitar o uso da GPU.
A biblioteca possuí algumas estruturas: </p>

<ul>
	<li>cores</li>
	<li>sprites</li>
	<li>blocos do background</li>
	<li>pixel na memória de sprites</li>
	<li>polígonos</li>
</ul>
Cada uma dessas estruturas servem para organizar os dados de maneira a facilitar o uso das funções pelo usuário, assim como facilitar a implementação das funções que enviam esses dados para a escrita na gpu

<h3 id="structCores">Struct Cores</h3>
<p>
A estrutura cores serve para definir os campos que uma cor deve possuir, que sao os valores referente a vermelho, verde e azul.
Essa estrutura foi utilizada nas demais estruturas que tinham a necessidade de um campo de cor, como bloco de background.

(imagem da struct)
</p>

<h3 id="structSprites">Struct Sprites</h3>

<p>
    A estrutura sprites serve para definir os campos que um sprite deve possuir, que são as coordenadas x e y, o offset que é o campo referente ao sprite que será exibido, o endereço do registrador que é referente a qual espaço na memoria o sprite irá ocupar e assim, quando for necessario alterar algum aspecto deste sprite, basta alterar o sprite armazenado nesta determinada posição de memoria e por ultimo sua visibilidade sendo 1 pra informa que o sprite será exibido e 0 para informa que o sprite não sera exibido.

    (imagem da struct)
</p>

<h3 id="structBgBlock">Struct Blocos de Background</h3>

<p>
    A estrutura de blocos de background reune as 2 informações principais necessarias do programador, a cor do bloco e qual a coordena x e y do bloco. A cor foi implementada utilizando a struct e as coordenadas x e y levam em conta a disposição dos blocos (80x60)e não dos pixels em si (640x480).

    (imagem da struct)
</p>


<h3 id="structPixel">Struct de um pixel na memoria</h3>
<p>Essa estrutura contem os campos necessarios para a criação de um pixel de um sprite, assim, a struct possui os campos de endereço de memoria que é referente a um endereço de memoria informado pelo usuario e um campo refenrete a cor desse pixel

(imagem da struct)

</p>

<h3 id="structPolygon">Struct Polígono</h3>
<p>
Essa Struct é utilizada para organizar os campos de um polígono sendo eles, coordenada x e y, endereço do polígono que é o campo referente a camada onde o polígono será exibido, tamanho, forma sendo 1 para triangulo e zero para quadrado e por ultimo cor
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


