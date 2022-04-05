// 20182558 ALESSANDRA SOUZA DA SILVA

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>

/* ULTILIZADA PARA ACHAR O MAXIMO E O MINIMO NO FILTRO DE ROTACAO*/

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

/* FUNCOES DA BIBLIOTECA */

void encontra_vizinhos(unsigned char **imagem, int *vetor_vizinhos, int i, int j, int altura, int largura, int* nvizinhos);
int calcula_vizinhos(int *vetor_vizinhos, int nvizinhos);
int cmpfunc(const void *a, const void *b);
void troca_valores(int *a, int *b);
int verfica_comentario(char *aux);
void libera_matriz(unsigned char **imagem, int linhas);
unsigned char **aloca_matriz(int linhas, int colunas);
void copia_imagem(unsigned char **imagem_original, unsigned char **imagem_copia, int linhas, int colunas);
