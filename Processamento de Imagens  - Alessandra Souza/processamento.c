// 20182558 ALESSANDRA SOUZA DA SILVA

#include "source/processamento.h"
#include "source/auxiliares.h"

/* REALIZA O FILTRO DA LIMIAR */
void filtro_negativo(unsigned char **imagem, int linhas, int colunas, int max)
{

    int i, j;
    /* CALULA PIXEL A PIXEL */
    for (i = 0; i < linhas; i++)
        for (j = 0; j < colunas; j++)
            /* ALTERA O VALOR DO PIXEL CENTRAL */
            imagem[i][j] = max - imagem[i][j];
}

/* REALIZA O FILTRO DA LIMIAR */
void filtro_limiar(unsigned char **imagem, int linhas, int colunas, int max, double limiar)
{
    int i, j;
    /* CALCULA O VALOR PROPPORCINAL DO MAX DA IMAGEM */
    int valor = max * limiar;
    /* CALULA PIXEL A PIXEL */
    for (i = 0; i < linhas; i++)
    {
        for (j = 0; j < colunas; j++)
        {
            /* FAZ A VERIFICACO DO PIXEL ATUAL */
            if (imagem[i][j] >= valor)
                imagem[i][j] = max;
            else
                imagem[i][j] = 0;
        }
    }
}

/* REALIZA O FILTRO DA MEDIA*/
void filtro_media(unsigned char **imagem, int linhas, int colunas)
{
    int i, j;
    /* ALOCA O VETOR PARA TODOS OS VIZINHOS DO PIXEL ATUAL */
    int *vetor_vizinhos = malloc(sizeof(int) * 9);
    /* ALOCA UMA MATRIZ COM OS NOVOS VALORES DE LINHA E COLUNA */
    unsigned char **imagem_copia = aloca_matriz(linhas, colunas);
    /* CALULA PIXEL A PIXEL */
    for (i = 1; i < linhas - 1; i++)
        for (j = 1; j < colunas - 1; j++)
        {
            /* ENCONTRA OS VIZINHOS DO PIXEL ATUAL */
            encontra_vizinhos(imagem, vetor_vizinhos, i, j);
            /* SOMA TODOS OS VALORES DOS VIZINHOS DO PIXEL ATUAL E FAZ A MEDIA*/
            imagem_copia[i][j] = calcula_vizinhos(vetor_vizinhos);
        }
    /* COPIA A NOVA IMAGEM PARA A ORIGINAL */
    copia_imagem(imagem_copia, imagem, linhas, colunas);
    /* LIBERA A MATRIZ */
    libera_matriz(imagem_copia, linhas);
    /* LIBERA O VETOR DOS VIZINHOS  */
    free(vetor_vizinhos);
}

/* REALIZA O FILTRO DA MEDIANA*/
void filtro_mediana(unsigned char **imagem, int linhas, int colunas, int mascara)
{
    int mediana, i, j, k, l, index;
    /* CALCULA O TAMANHO DO VETOR DE ACORDO COM A MASCARA */
    int pos = mascara * mascara;
    /* ALOCA O VETOR PARA TODOS OS VIZINHOS DO PIXEL ATUAL */
    int *vetor_vizinhos = malloc(sizeof(int) * pos);
    /* CALULA PIXEL A PIXEL */
    for (i = 0; i < linhas; i++)
        for (j = 0; j < colunas; j++)
        {
            /* INCIA A VARIAVEL RESPOSAVEL POR ALTERNAR O INDEX DO VETOR DE VIZINHOS */
            index = 0;
            /* A VARIAVEL K FICA RESPONSAVEL POR ARMAZENAR O INDEX DA LINHA ATUAL DA MASCARA */
            for (k = 0; k < mascara && k + i < linhas; k++)
                /* A VARIAVEL L FICA RESPONSAVEL POR ARMAZENAR O INDEX DA COLUNA ATUAL DA MASCARA */
                for (l = 0; l < mascara && l + j < colunas; l++)
                {
                    /* AO VETOR DE VIZINHOS RECEBE AS VALORES DA POSICAO POR ONDE A MASCA PASSA*/
                    vetor_vizinhos[index] = imagem[k + i][l + j];
                    index++;
                }
            /* REALIZA A ORDENACAO DO VETOR */
            qsort(vetor_vizinhos, pos, sizeof(int), cmpfunc);
            /* ENCONTRA O VALOR NA METADE DA SEQUENCIA */
            mediana = vetor_vizinhos[(index / 2)];
            /* ALTERA O VALOR DO PIXEL CENTRAL */
            imagem[i][j] = mediana;
        }
    /* LIBERA O VETOR DOS VIZINHOS  */
    free(vetor_vizinhos);
}

/* CALCULA O NOVO VALOR DO PIXEL CENTRAL */
int calcula_lbp(int *vetor_vizinhos, int pixel)

{
    int potencia = 0;
    int soma = 0;
    int i;
    for (i = 0; i < 8; i++, potencia++)
    {
        /*SE O VALOR DA POSICAO ATUAL DO VETOR FOR
        MAIOR OU IGUAL AO PIXEL CENTRAL,
        DEVE-SE SOMAR O VALOR DE 2
        NA POTENCIA DA MASCARA ATUAL*/
        if (vetor_vizinhos[i] >= pixel)
        {
            /* MASCARA :>> 2ˆN, ONDE N: {0,1,2,..,7} */
            soma += pow(2, potencia);
        }
    }
    return soma;
}

/* REALIZA O FILTRO DE LBP*/
void filtro_lbp(unsigned char **imagem, int linhas, int colunas)
{

    /* ALOCA UMA VETOR PARA OS VALORES DO PIXEL CENTRAL */
    int *vetor_vizinhos = malloc(sizeof(int) * 9);

    int i, j, pixel;

    /* CALULA PIXEL A PIXEL */
    for (i = 1; i < linhas - 1; i++)
        for (j = 1; j < colunas - 1; j++)
        {
            /* ENCONTRA OS VIZINHOS DO PIXEL ATUAL */
            encontra_vizinhos(imagem, vetor_vizinhos, i, j);
            /* RESPEITANDO A REGRA DO LBP, CALCULA O NOVO VALOR PARA O PIXEL CENTRAL*/
            pixel = calcula_lbp(vetor_vizinhos, imagem[i][j]);
            /* ALTERA O VALOR DO PIXEL CENTRAL */
            imagem[i][j] = pixel;
        }
    /* LIBERA O VETOR DOS VIZINHOS  */
    free(vetor_vizinhos);
}

/* REALIZA O FILTRO DE ROTACAO SIMPLES*/
unsigned char **filtro_rotacao_simples(unsigned char **imagem, int *linhas, int *colunas)
{
    int i, j;

    /* ALOCA UMA MATRIZ COM OS NOVOS VALORES DE LINHA E COLUNA */
    unsigned char **imagem_copia = aloca_matriz(*colunas, *linhas);

    /* ROTACIONA PIXEL A PIXEL */
    for (i = 0; i < *linhas; i++)
        for (j = 0; j < *colunas; j++)
            imagem_copia[j][*linhas - i - 1] = imagem[i][j];

    /* LIBERA IMAGEM ORIGINAL */
    libera_matriz(imagem, *linhas);

    /* TROCA OS VALORES DE LINHA E COLUNA, PARA SE ADEQUAR PARA A NOVA IMAGEM */
    troca_valores(linhas, colunas);

    /* RETORNA A NOVA IMAGEM */
    return imagem_copia;
}

/* REALIZA O FILTRO DE ROTACAO LIVRE*/
unsigned char **filtro_rotacao_livre(unsigned char **imagem, int *linhas, int *colunas, int rotacao)
{
    /* TRANSFORMA PARA RADIANO */
    double angulo = -rotacao * 2 * M_PI / 360;

    double seno = sin(angulo);   /* CALCULA SENO */
    double coseno = cos(angulo); /* CALCULA COSENO */

    /* CALCULO DOS PONTOS DA IMAGEM ORIGINAL */
    float ponto1x = (-*linhas * seno);
    float ponto1y = (*linhas * coseno);
    float ponto2x = (*colunas * coseno - *linhas * seno);
    float ponto2y = (*linhas * coseno + *colunas * seno);
    float ponto3x = (*colunas * coseno);
    float ponto3y = (*colunas * seno);

    float minimo_x = min(0, min(ponto1x, min(ponto2x, ponto3x)));
    float minimo_y = min(0, min(ponto1y, min(ponto2y, ponto3y)));
    float maximo_x = max(ponto1x, max(ponto2x, ponto3x));
    float maximo_y = max(ponto1y, max(ponto2y, ponto3y));

    /* ENCONTRA O NOVO TAMANHO DA IMAGEM A PARTIR DO ANGULO */
    int nova_colunas = (int)ceil(fabs(maximo_x) - minimo_x);
    int nova_linhas = (int)ceil(fabs(maximo_y) - minimo_y);

    /* ALOCA UMA MATRIZ COM OS NOVOS VALORES DE LINHA E COLUNA */
    unsigned char **imagem_copia = aloca_matriz(nova_colunas, nova_linhas);

    /* ROTACIONA PIXEL A PIXEL */
    int i, j;

    for (int i = 0; i < nova_colunas; i++)
    {
        for (int j = 0; j < nova_linhas; j++)
        {
            /* ENCONTRA AS NOVAS POSICOES DO PIXEL DA IMAGEM ORIGINAL PARA A ROTACIONADA */
            int posicao_x = (int)((i + minimo_x) * coseno + (j + minimo_y) * seno);
            int posicao_Y = (int)((j + minimo_y) * coseno - (i + minimo_x) * seno);

            /* COMO NEM SEMPRE AS POSICOES NAO VAO EXISTIR NA IMAGEM ORIGINAL, NESSE CASO VIRA BRANCO */
            if (posicao_x >= 0 && posicao_x < *linhas && posicao_Y >= 0 && posicao_Y < *colunas)

                imagem_copia[i][j] = imagem[posicao_x][posicao_Y];
            else
                imagem_copia[i][j] = 255;
        }
    }
    /* LIBERA IMAGEM ORIGINAL */
    libera_matriz(imagem, *linhas);

    /* TROCA OS VALORES DE LINHA E COLUNA, PARA SE ADEQUAR PARA A NOVA IMAGEM */
    *linhas = nova_colunas;
    *colunas = nova_linhas;

    /* RETORNA A NOVA IMAGEM */
    return imagem_copia;
}