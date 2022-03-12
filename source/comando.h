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

typedef struct linha_comando
{
    char *comando;
    char *entrada;
    char *saida;
    bool impressao_stdin;
    bool leitura_stdin;
    bool mascara;
    bool limiar;
    bool rotacao;
    int valor_mascara;
    double valor_limiar;
    int valor_rotacao;
} linha_comando;

void ler_linha_comando(int argc, char const *argv[], linha_comando *linhaComando);
FILE *abre_arquivo(char *nome, bool entrada);
