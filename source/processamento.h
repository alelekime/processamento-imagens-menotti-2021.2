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

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

void filtro_negativo(unsigned char **imagem, int tamanho, int largura, int max);
void filtro_limiar(unsigned char **imagem, int tamanho, int largura, int max, double limiar);
void encontra_vizinhos(unsigned char **imagem, int *vetor_vizinhos, int i, int j);
int calcula_vizinhos(int *vetor_vizinhos);
void filtro_media(unsigned char **imagem, int tamanho, int largura);
int cmpfunc(const void *a, const void *b);
void filtro_mediana(unsigned char **imagem, int tamanho, int largura, int mascara);
int calcula_lbp(int *vetor_imagem, int pixel);
void filtro_lbp(unsigned char **imagem, int tamanho, int largura);
unsigned char **filtro_rotacao(unsigned char **imagem, int *linhas, int *colunas, int rotacao);
