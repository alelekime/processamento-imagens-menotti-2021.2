// 20182558 ALESSANDRA SOUZA DA SILVA

#include "source/auxiliares.h"

/* ENCONTRA OS OITO VIZINHOS E O PIXEL ATUAL */
void encontra_vizinhos(unsigned char **imagem, int *vetor_vizinhos, int i, int j, int altura, int largura, int* nvizinhos)
{
	*nvizinhos = 0;
	if (i > 0        && j >         0)  vetor_vizinhos[(*nvizinhos)++] = imagem[i - 1][j - 1];
	if (i > 0                        )  vetor_vizinhos[(*nvizinhos)++] = imagem[i - 1][j    ];
	if (i > 0        && j < largura-1)  vetor_vizinhos[(*nvizinhos)++] = imagem[i - 1][j + 1];
	if (                j >         0)  vetor_vizinhos[(*nvizinhos)++] = imagem[i    ][j - 1];
                                        vetor_vizinhos[(*nvizinhos)++] = imagem[i    ][j    ]; // Menotti - não deve ser considerado para LBP
	if (                j < largura-1)  vetor_vizinhos[(*nvizinhos)++] = imagem[i    ][j + 1];
	if (i < altura-1 && j >         0)  vetor_vizinhos[(*nvizinhos)++] = imagem[i + 1][j - 1];
	if (i < altura-1                 )  vetor_vizinhos[(*nvizinhos)++] = imagem[i + 1][j    ];
	if (i < altura-1 && j < largura-1)  vetor_vizinhos[(*nvizinhos)++] = imagem[i + 1][j + 1];
}

/* CALCULA A MEDIA DOS VIZINHOS MAIS ELE MESMO*/
int calcula_vizinhos(int *vetor_vizinhos, int nvizinhos) // Menotti
{
    int i;
    int soma = 0;
    for (i = 0; i < nvizinhos; i++) 
        /* SOMA OS VALORES DE TODOS OS VIZINHOS E ELE MESMO*/
        soma += vetor_vizinhos[i];
    /* REALIZA A MEDIA */
    return soma / nvizinhos;
}

/* FUNCAO NECESSARIA PARA USAR O QSORT*/
int cmpfunc(const void *a, const void *b)
{
    return (*(unsigned char*)a - *(unsigned char*)b); // Menotti
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
