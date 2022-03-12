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

void troca_valores(int *a, int *b);
int verfica_comentario(char *aux);
void libera_matriz(unsigned char **imagem, int linhas);
unsigned char **aloca_matriz(int linhas, int colunas);
void copia_imagem(unsigned char **imagem_original, unsigned char **imagem_copia, int linhas, int colunas);
