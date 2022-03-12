// 20182558 ALESSANDRA SOUZA DA SILVA

#include "source/acesso.h"

void leitura_info(ponteiros_arquivos *input)
{
    char *aux = malloc(sizeof(char) * 512);
    input->infoImagem->tipo_imagem = malloc(sizeof(char) * 512);
    fgets(aux, 512, input->arquivo_entrada);
    strncpy(input->infoImagem->tipo_imagem, aux, (strlen(aux) - 1));
    fgets(aux, 512, input->arquivo_entrada);
    if (verfica_comentario(aux))
        fscanf(input->arquivo_entrada, "%d %d", &input->infoImagem->colunas, &input->infoImagem->linhas);
    else
        sscanf(aux, "%d %d", &input->infoImagem->colunas, &input->infoImagem->linhas);
    fscanf(input->arquivo_entrada, "%d", &input->infoImagem->max_imagem);
    free(aux);
}

void escreve_info(ponteiros_arquivos *input)
{
    fputs(input->infoImagem->tipo_imagem, input->arquivo_saida);
    fputs("\n", input->arquivo_saida);
    fprintf(input->arquivo_saida, "%d %d\n", input->infoImagem->colunas, input->infoImagem->linhas);
    fprintf(input->arquivo_saida, "%d\n", input->infoImagem->max_imagem);
}

void le_imagem(ponteiros_arquivos *input)
{

    leitura_info(input);
    int i, j;
    int linhas = input->infoImagem->linhas;
    int colunas = input->infoImagem->colunas;
    input->infoImagem->imagem = aloca_matriz(linhas, colunas);

    for (i = 0; i < linhas; i++)
        for (j = 0; j < colunas; j++)
            if (!strcmp(input->infoImagem->tipo_imagem, "P5"))
                fread(&input->infoImagem->imagem[i][j], sizeof(unsigned char), 1, input->arquivo_entrada);
            else
                fscanf(input->arquivo_entrada, "%d ", (int *)&input->infoImagem->imagem[i][j]);

    fclose(input->arquivo_entrada);
}

void escreve_imagem(ponteiros_arquivos *input)
{
    escreve_info(input);
    int i, j;
    int linhas = input->infoImagem->linhas;
    int colunas = input->infoImagem->colunas;

    for (i = 0; i < linhas; i++)
        for (j = 0; j < colunas; j++)
        {
            if (!strcmp(input->infoImagem->tipo_imagem, "P5"))
                fwrite(&input->infoImagem->imagem[i][j], sizeof(unsigned char), 1, input->arquivo_saida);
            else
                fprintf(input->arquivo_saida, "%d ", input->infoImagem->imagem[i][j]);
        }

    fclose(input->arquivo_saida);
}