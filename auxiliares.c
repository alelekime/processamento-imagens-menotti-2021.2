// 20182558 ALESSANDRA SOUZA DA SILVA

#include "source/auxiliares.h"

void troca_valores(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void libera_matriz(unsigned char **imagem, int linhas)
{
    int i;
    for (i = 0; i < linhas; i++)
        free(imagem[i]);
    free(imagem);
}

unsigned char **aloca_matriz(int linhas, int colunas)
{
    int i;

    unsigned char **imagem = malloc(sizeof(unsigned char *) * (linhas));
    for (i = 0; i < linhas; i++)
    {
        imagem[i] = malloc(sizeof(unsigned char) * (colunas));
    }
    return imagem;
}

void copia_imagem(unsigned char **imagem_original, unsigned char **imagem_copia, int linhas, int colunas)
{
    int i, j;
    for (i = 0; i < linhas; i++)
    {
        for (j = 0; j < colunas; j++)
        {
            imagem_copia[i][j] = imagem_original[i][j];
            // printf("%c ", input->infoImagem->imagem[i][j].P5_valor);
        }
    }
}

int verfica_comentario(char *aux)
{
    if (aux[0] == '#')
        return true;
    else
        return false;
}