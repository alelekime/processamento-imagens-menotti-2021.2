// 20182558 ALESSANDRA SOUZA DA SILVA

#include "source/auxiliares.h"

/* ENCONTRA OS OITO VIZINHOS E O PIXEL ATUAL */
void encontra_vizinhos(unsigned char **imagem, int *vetor_vizinhos, int i, int j)
{
    vetor_vizinhos[0] = imagem[i - 1][j - 1];
    vetor_vizinhos[1] = imagem[i - 1][j];
    vetor_vizinhos[2] = imagem[i - 1][j + 1];
    vetor_vizinhos[3] = imagem[i][j - 1];
    vetor_vizinhos[4] = imagem[i][j + 1];
    vetor_vizinhos[5] = imagem[i + 1][j - 1];
    vetor_vizinhos[6] = imagem[i + 1][j];
    vetor_vizinhos[7] = imagem[i + 1][j + 1];
    vetor_vizinhos[8] = imagem[i][j];
}

/* CALCULA A MEDIA DOS VIZINHOS MAIS ELE MESMO*/
int calcula_vizinhos(int *vetor_vizinhos)
{
    int i;
    int soma = 0;
    for (i = 1; i < 9; i++)
        /* SOMA OS VALORES DE TODOS OS VIZINHOS E ELE MESMO*/
        soma += vetor_vizinhos[i];
    /* REALIZA A MEDIA */
    return soma / 9;
}

/* FUNCAO NECESSARIA PARA USAR O QSORT*/
int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

/* TROCA O VALOR DE DOIS PONTEIROS */
void troca_valores(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/* DESALOCA A MATRIZ */
void libera_matriz(unsigned char **imagem, int linhas)
{
    int i;
    for (i = 0; i < linhas; i++)
        free(imagem[i]);
    free(imagem);
}

/* ALOCA A MATRIZ DE VETORES DE VETORES */
unsigned char **aloca_matriz(int linhas, int colunas)
{
    int i;

    unsigned char **imagem = malloc(sizeof(unsigned char *) * (linhas));
    for (i = 0; i < linhas; i++)
        imagem[i] = malloc(sizeof(unsigned char) * (colunas));

    return imagem;
}

/* COPIA A IMAGEM DE UMA IMAGEM ORIGINAL PARA A COPIA */
void copia_imagem(unsigned char **imagem_original, unsigned char **imagem_copia, int linhas, int colunas)
{
    int i, j;
    for (i = 0; i < linhas; i++)
        for (j = 0; j < colunas; j++)
            imagem_copia[i][j] = imagem_original[i][j];
}

/* VERIFICA SE O VETOR PASSADO É UM COMENTARIO*/
int verfica_comentario(char *aux)
{
    if (aux[0] == '#')
        return true;
    else
        return false;
}