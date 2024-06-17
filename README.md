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
	
[Sobre o projeto](README.md#sobre-o-projeto) • [Instalação](README.md#instalação) • [Solução geral](README.md#solução-geral) • [Driver](README.md#driver-colenda-1) • [Biblioteca](README.md#biblioteca-colenda) • [Testes](README.md#produto-e-testes-realizados)
	

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
<summary><h3 style="font-weight: bold">Requisitos</h3></summary>

- Possuir conexão com internet;
- Possuir instalado o compilador gcc;
- Possuir instalado o Git ;
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
O produto desenvolvido implementa a intercomunicação entre o software e o dispositivo gráfico CoLenda. O fluxo de comunicação entre a aplicação de usuário, o módulo kernel e o hardware é esquematizado na figura 3.
<div align="center">
  <figure>  
    <img src="docs/images/solucao_geral.png">
    <figcaption>
      <p align="center"><b>Figura 3</b> - Esquema em blocos da solução geral </p>
      <p align="center">Fonte:Elaboração própria</p>
    </figcaption>
  </figure>
</div>

O fluxo de comunicação inicia-se com a aplicação do usuário que, por meio dos recursos disponibilizados pela biblioteca CoLenda tais como estruturas e funções, gerencia os dados dos elementos a serem exibidos no monitor e as chamadas das respectivas funções da *lib* para realizar as exibições na tela.

Por sua vez, a biblioteca atua como uma mediadora entre a aplicação de usuário e o driver CoLenda, gerenciando as chamadas de sistema necessárias e a conversão das solicitações recebidas para o stream de bit compreensível pelo driver.

Por fim, o driver gerencia os sinais de entrada e saída do hardware diretamente pelo seu barramento de dados a fim de enviar as instruções recebidas da biblioteca.
## Driver CoLenda
## Biblioteca CoLenda
A biblioteca desenvolvida provê uma abstração da comunicação com o driver de dispositivo, facilitando a interação do usuário com o módulo kernel do hardware.
Esta *lib* disponibiliza constantes para a seleção de sprites, estruturas para a organização dos elementos a serem exibidos, funções respectivas às instruções do processador gráfico e pseudo-instruções, tal como *clear*, que executam conjuntos de instruções.
> [!NOTE]
> Os sprites disponíveis para seleção estão salvos em hardware no processador gráfico.
> Nenhum deles foi criado pela biblioteca

> [!NOTE]
> As pseudo-instruções são funções da biblioteca que podem ser chamadas

<details >
<summary><b>Constantes de sprite</b></summary>

As constantes de sprite implementadas visam facilitar a escolha do sprite, pois abstraem o número relacionado ao endereço em que um sprite específico está localizado.

(colocar os defines)

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
	
| Função | Argumento | Instrução relacionada |
|  -----------  | ----------- |---- |
|Setar pixel | Struct pixel | WSM |
|Setar cor de fundo | Struct cor | WRB |
|Setar bloco de fundo | Struct bloco de background | WSM |
|Setar sprite | Struct sprite | WRB |
|Setar polígono | Struct polígono | DP |
	
</details>

<details>
<summary ><b>Pseudo-instruções</b></summary>

| Função | Descrição | Argumento |
|  -----------  | ----------- |----------- |
| Desenhar linha vertical | Desenha uma linha vertical utilizando blocos de background. Chama a função setar bloco de background n vezes alterando apenas a coordenada y | Coordenadas iniciais x e y, tamanho (n) e  cor (struct)|
| Desenhar linha horizontal | Desenha uma linha vertical utilizando blocos de background. Chama a função setar bloco de background n vezes alterando apenas a coordenada x | Coordenadas iniciais x e y, tamanho (n) e  cor (struct)|
| Desenhar bloco de background | Seta um bloco de background. Dispensa a instância da struct| Coordenadas iniciais x e y, e cor (struct)|
| Clear | Reseta a tela| - |


</details>

<details >
<summary><b>Funções internas  auxiliares</b></summary>
	
- função para escrever no buffer do driver as instruções (gerencia a chamada de sistema write)
- b
- c

</details>

<details >
<summary ><b>Validação de valores</b></summary>

A biblioteca apresenta recursos para validação dos valores inseridos pelo usuário, pois como as instruções possuem tamanhos e campos distintos, foi imprescindível a existência de recursos para validar essas informações. A detecção de um erro retorna um valor de erro à aplicação do usuário  

(mostrar os trechos de validação das informações)
</details>	


## Produto e testes realizados
## Conclusão
## Referências


