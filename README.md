# Processamento de Imagens
O processamento digital de imagens usa intensivamente vetores e matrizes. Uma imagem é geralmente representada como uma matriz de pixels, onde cada pixel é descrito por um ou mais valores inteiros que indicam seus níveis de cor ou de luminosidade. Por isso, processar imagens é uma ótima forma de exercitar o uso de matrizes.

<http://wiki.inf.ufpr.br/maziero/doku.php?id=prog2:processamento_de_imagens>

# Filtros de imagem

Este projeto visa construir filtros simples para imagens digitais em níveis de cinza, no formato PGM (P2 e P5) com pixels de 8 bits (1 byte).

## Filtro negativo

O filtro negativo consiste em converter cada pixel da imagem em seu complemento. Sendo max o valor máximo para um pixel na imagem, o complemento de um pixel com valor v seria max-v.

Forma de chamada:

`pgmnega -i input -o output`


## Filtro de rotação simples

O filtro de rotação gira uma imagem em 90° no sentido horário.

Forma de chamada:

`pgmrotacao -i input -o output`


## Filtro de rotação livre

O filtro de rotação gira uma imagem em um ângulo θ (>0) no sentido horário, em relação ao seu centro (vide rotação de imagens 2D).

**Requisitos:**

O tamanho da imagem de saída deve ser ajustado para não cortar os cantos da imagem.
Os espaços vazios gerados pela rotação devem ser preenchidas com a cor branca.
O ângulo de rotação é informado pela opção -a; se não for informado, por default θ = 90º.

Forma de chamada:

`pgmrotacao -a N -i input -o output`


## Filtro de limiar

O filtro de limiar (threshold filter) converte uma imagem em tons de cinza em um imagem em preto-e-branco (2 cores). A forma mais simples de fazer isso é comparar o valor de cada pixel com um limiar pré-definido: se o valor do pixel for igual ou superior ao limiar, ele vira branco (v=max), caso contrário ele vira preto (v=0).

Forma de chamada:

`pgmlimiar -l N -i input -o output`

onde N é um limiar real entre 0.0 (0% do valor máximo) e 1.0 (100% do valor máximo). Caso o limiar não esteja definido, assume-se que seja 50%.


## Filtro de redução de ruído pela média

O filtro da média é usado para para “limpar” uma imagem, ou seja, reduzir o seu nível de ruído. O algoritmo é básico bem simples: para cada pixel, seu valor deve ser substituído pela média de todos os 9 pixels vizinhos (incluindo ele mesmo).

Deve ser tomado cuidado especial ao tratar os pixels nas primeiras e últimas linhas ou colunas, pois eles não têm todos os vizinhos. Nesses casos, devem ser considerados no cálculo somente os vizinhos existentes.

A imagem processada deve ser armazenada em uma segunda matriz, para que não se misturem valores novos e velhos no cálculo dos pixels.

Forma de chamada:

`pgmmedia -i input -o output`

## Filtro da mediana

O filtro da mediana reduz o nível de ruído de uma imagem sem prejudicar muito sua nitidez. Este filtro consiste basicamente em substituir o valor de um pixel pelo valor da mediana de seus pixels vizinhos. O número de vizinhos a considerar é definido por uma máscara, ou seja, a matriz de vizinhos que circunda o pixel a tratar (incluindo ele mesmo):

**Requisitos:**

O tamanho da máscara é um inteiro positivo ímpar, que pode ser informado na linha de comando (opção -m); caso não seja informado, o valor default é 3, para uma máscara de 3×3 pixels.
Os pixels nas bordas da imagem não têm todos os vizinhos e portanto não devem ser filtrados.
Para ordenar os valores dos pixels deve ser usada a função qsort da biblioteca C (man qsort).

Forma de chamada:

`pgmmediana -m N -i input -o output` 


## Filtro LBP (Local Binary Patterns)

LBP (Local Binary Patterns) ou Padrões Binários Locais, é um descritor de textura muito utilizado em algoritmos de reconhecimento de imagens. O funcionamento desse filtro é simples: para cada pixel de uma imagem com 256 níveis de cinza, seleciona-se uma vizinhança de 8 pixels. O valor LBP é então calculado para o pixel central e armazenado na imagem destino, que possui as mesmas dimensões da imagem original.

Para o cálculo do LBP de um pixel, usa-se uma máscara com valores 2n, com n = {0, …, 7}, ou seja: 1, 2, 4, 8, 16, 32, 64 e 128. O exemplo abaixo ilustra o cálculo de LBP para o pixel com valor 6:

**Cálculo de LBP**

Considere o pixel central com valor 6 e seus oito vizinhos na imagem (a). O valor do pixel central é utilizado como limiar e todos os pixels com valor de intensidade maior ou igual a ele recebem 1, caso contrário, 0 (b). Esses valores são então multiplicados pela máscara (c ), resultando então nos valores apresentados em (d). O valor LBP do pixel 6 é dado pela soma desses valores, ou seja LPB = 1+8+32+128 = 169. Note que essa codificação garante valores LBP entre 0 e 255.

Forma de chamada:

`pgmlbp -i input -o output`
