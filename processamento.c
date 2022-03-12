// 20182558 ALESSANDRA SOUZA DA SILVA

#include "source/processamento.h"
#include "source/auxiliares.h"

void filtro_negativo(unsigned char **imagem, int linhas, int colunas, int max)
{

    int i, j;
    for (i = 0; i < linhas; i++)
        for (j = 0; j < colunas; j++)
            imagem[i][j] = max - imagem[i][j];
}

void filtro_limiar(unsigned char **imagem, int linhas, int colunas, int max, double limiar)
{

    int i, j;
    int valor = max * limiar;
    for (i = 0; i < linhas; i++)
    {
        for (j = 0; j < colunas; j++)
        {
            if (imagem[i][j] >= valor)
                imagem[i][j] = max;
            else
                imagem[i][j] = 0;
        }
    }
}
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
int calcula_vizinhos(int *vetor_vizinhos)
{
    int i;
    int soma = 0;
    for (i = 1; i < 9; i++)
        soma += vetor_vizinhos[i];
    return soma / 9;
}
void filtro_media(unsigned char **imagem, int linhas, int colunas)
{
    int i, j;
    int *vetor_vizinhos = malloc(sizeof(int) * 9);

    unsigned char **imagem_copia = aloca_matriz(linhas, colunas);
    for (i = 1; i < linhas - 1; i++)
        for (j = 1; j < colunas - 1; j++)
        {
            encontra_vizinhos(imagem, vetor_vizinhos, i, j);
            imagem_copia[i][j] = calcula_vizinhos(vetor_vizinhos);
        }

    copia_imagem(imagem_copia, imagem, linhas, colunas);
    libera_matriz(imagem_copia, linhas);
}

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void filtro_mediana(unsigned char **imagem, int linhas, int colunas, int mascara)
{
    int mediana, i, j, k, l;
    int pos = mascara * mascara;
    int *vetor_imagem = malloc(sizeof(int) * pos);

    for (i = 0; i < linhas; i++)
        for (j = 0; j < colunas; j++)
        {
            int index = 0;
            for (k = 0; k < mascara && k + i < linhas; k++)

                for (l = 0; l < mascara && l + j < colunas; l++)
                {
                    vetor_imagem[index] = imagem[k + i][l + j];
                    index++;
                }
            qsort(vetor_imagem, pos, sizeof(int), cmpfunc);
            mediana = vetor_imagem[(index / 2)];
            imagem[i][j] = mediana;
            ;
        }
}

int calcula_lbp(int *vetor_imagem, int pixel)

{
    int potencia = 0;
    int soma = 0;
    int i;
    for (i = 0; i < 8; i++, potencia++)
    {
        if (vetor_imagem[i] >= pixel)
        {
            soma = pow(2, potencia);
        }
    }
    return soma;
}

void filtro_lbp(unsigned char **imagem, int linhas, int colunas)
{
    int *vetor_vizinhos = malloc(sizeof(int) * 9);

    int i, j, pixel;
    for (i = 1; i < linhas - 1; i++)
        for (j = 1; j < colunas - 1; j++)
        {
            encontra_vizinhos(imagem, vetor_vizinhos, i, j);
            pixel = calcula_lbp(vetor_vizinhos, imagem[i][j]);
            imagem[i][j] = pixel;
        }
}

unsigned char **filtro_rotacao(unsigned char **imagem, int *linhas, int *colunas, int rotacao)
{
    int i, j;
    // printf(" :>> %d\n", imagem[4][2]);
    double angulo = -rotacao * 2 * M_PI / 360;

    double seno = sin(angulo);
    double coseno = cos(angulo);

    float Point1x = (-*linhas * seno);
    float Point1y = (*linhas * coseno);
    float Point2x = (*colunas * coseno - *linhas * seno);
    float Point2y = (*linhas * coseno + *colunas * seno);
    float Point3x = (*colunas * coseno);
    float Point3y = (*colunas * seno);

    float minx = min(0, min(Point1x, min(Point2x, Point3x)));
    float miny = min(0, min(Point1y, min(Point2y, Point3y)));
    float maxx = max(Point1x, max(Point2x, Point3x));
    float maxy = max(Point1y, max(Point2y, Point3y));

    int DestBitmapWidth = (int)ceil(fabs(maxx) - minx);
    int DestBitmapHeight = (int)ceil(fabs(maxy) - miny);
    printf("DestBitmapWidth, DestBitmapHeight) :>> %d %d\n", DestBitmapWidth, DestBitmapHeight);
    unsigned char **imagem_copia = aloca_matriz(DestBitmapWidth, DestBitmapHeight);
    for (int x = 0; x < DestBitmapWidth; x++)
    {
        for (int y = 0; y < DestBitmapHeight; y++)
        {
            int SrcBitmapx = (int)((x + minx) * coseno + (y + miny) * seno);
            int SrcBitmapy = (int)((y + miny) * coseno - (x + minx) * seno);
            // printf("x,y :>> %d %d\n", x, y);
            if (SrcBitmapx >= 0 && SrcBitmapx < *linhas && SrcBitmapy >= 0 &&
                SrcBitmapy < *colunas)
            {
                // printf("SrcBitmapx , SrcBitmapy :>> %d %d :>>%d\n", SrcBitmapx, SrcBitmapy, imagem[SrcBitmapx][SrcBitmapy]);

                imagem_copia[x][y] = imagem[SrcBitmapx][SrcBitmapy];
            }
            else
                imagem_copia[x][y] = 255;
        }
    }
    libera_matriz(imagem, *linhas);

    *linhas = DestBitmapHeight;
    *colunas = DestBitmapWidth;
    troca_valores(linhas, colunas);
    return imagem_copia;
}