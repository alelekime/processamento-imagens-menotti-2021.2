// 20182558 ALESSANDRA SOUZA DA SILVA

#include "source/acesso.h"

/* LE AS INFORMACOES DE TIPO, LINHAS, COLUNAS E MAX */
void leitura_info(ponteiros_arquivos *input)
{
    /* ALOCA UM VETOR PARA ARMAZENAR AS LEITURAS DO ARQUIVO */
    char *aux = malloc(sizeof(char) * 512);
    /* ALOCA A VARIAVEL QUE VAI ARMAZENARO TIPO DA IMAGEM */
    input->infoImagem->tipo_imagem = malloc(sizeof(char) * 2);
    /* LE A PRIMEIRA LINHA DA IMAGEM - TIPO DA IMAGEM */
    fgets(aux, 512, input->arquivo_entrada);
    /* TIRA O \N DO FINAL DA LINHA */
    strncpy(input->infoImagem->tipo_imagem, aux, (strlen(aux) - 1));
    /* LE A SEGUNDA LINHA DA IMAGEM - LINHA E COLUNA OU COMENTARIO */
    fgets(aux, 512, input->arquivo_entrada);
    /* VERIFICA SE É COMENTARIO */
    if (verfica_comentario(aux))
        /*SE SIM, LE A PROXIMA LINHA - LINHA E COLUNA*/
        fscanf(input->arquivo_entrada, "%d %d", &input->infoImagem->colunas, &input->infoImagem->linhas);
    else
        /* SE NAO COPIA PARA AS VARIAVEIS CORRESPONDENTES O VALOR DE LINHA E COLUNA */
        sscanf(aux, "%d %d", &input->infoImagem->colunas, &input->infoImagem->linhas);
    /* LE A TERCEIRA/QUARTA LINHA DA IMAGEM - MAX */
    fscanf(input->arquivo_entrada, "%d", &input->infoImagem->max_imagem);
    /* LIBERA O AUX */
    free(aux);
}
/* ESCREVE AS INFORMACOES DE TIPO, LINHAS, COLUNAS E MAX */
void escreve_info(ponteiros_arquivos *input)
{
    /* ESCREVE - TIPO DA IMAGEM */
    fputs(input->infoImagem->tipo_imagem, input->arquivo_saida);
    /* ESCREVE \N */
    fputs("\n", input->arquivo_saida);
    /* ESCREVE - LINHA E COLUNA */
    fprintf(input->arquivo_saida, "%d %d\n", input->infoImagem->colunas, input->infoImagem->linhas);
    /* ESCREVE - MAX */
    fprintf(input->arquivo_saida, "%d\n", input->infoImagem->max_imagem);
}

/* REALIZA A LEITURA DA IMGEM */
void le_imagem(ponteiros_arquivos *input)
{
    /* LE AS INFORMACOES DE TIPO, LINHAS, COLUNAS E MAX */
    leitura_info(input);
    int i, j;
    int linhas = input->infoImagem->linhas;
    int colunas = input->infoImagem->colunas;
    /* ALOCA A MATRIZ QUE VAI SER USADA PARA ARMAZENAR A IMAGEM */
    input->infoImagem->imagem = aloca_matriz(linhas, colunas);

    /* LE PIXEL A PIXEL */
    for (i = 0; i < linhas; i++)
        for (j = 0; j < colunas; j++)
            /* VERIFICA SE O TIPO DA IMAGEM É P5 OU P2 */
            if (!strcmp(input->infoImagem->tipo_imagem, "P5"))
                /* SE FOR P5, DEVE SE LER EM BLOCAS DE BINARIOS */
                fread(&input->infoImagem->imagem[i][j], sizeof(unsigned char), 1, input->arquivo_entrada);
            else
                /* SE FOR P2, PODE SER UMA LEITURA SIMPLES */
                fscanf(input->arquivo_entrada, "%d ", (int *)&input->infoImagem->imagem[i][j]);

    /* FECHA O ARQUIVO */
    fclose(input->arquivo_entrada);
}
/* REALIZA A ESCRITA DA IMGEM */
void escreve_imagem(ponteiros_arquivos *input)
{
    /* ESCREVE AS INFORMACOES DE TIPO, LINHAS, COLUNAS E MAX */
    escreve_info(input);
    int i, j;
    int linhas = input->infoImagem->linhas;
    int colunas = input->infoImagem->colunas;

    /* ESCREVE PIXEL A PIXEL */
    for (i = 0; i < linhas; i++)
        for (j = 0; j < colunas; j++)
            /* VERIFICA SE O TIPO DA IMAGEM É P5 OU P2 */
            if (!strcmp(input->infoImagem->tipo_imagem, "P5"))
                /* SE FOR P5, DEVE SE IMPRIMIR EM BLOCAS DE BINARIOS */
                fwrite(&input->infoImagem->imagem[i][j], sizeof(unsigned char), 1, input->arquivo_saida);
            else
                /* SE FOR P2, PODE SER UMA IMPRESSAO SIMPLES */
                fprintf(input->arquivo_saida, "%d ", input->infoImagem->imagem[i][j]);

    /* FECHA O ARQUIVO */
    fclose(input->arquivo_saida);
}