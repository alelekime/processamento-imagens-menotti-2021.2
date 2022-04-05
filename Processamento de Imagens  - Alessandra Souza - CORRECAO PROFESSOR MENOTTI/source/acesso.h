// 20182558 ALESSANDRA SOUZA DA SILVA

#include "auxiliares.h"

/* STRUCT RESPONSAVEL POR ARMAZENAR OS DADOS DA IMAGEM */

typedef struct info_imagem
{
    char *tipo_imagem;
    unsigned char **imagem;
    int linhas;
    int colunas;
    int max_imagem;
} info_imagem;

/* STRUCT RESPONSAVEL POR ARMAZENAR OS PONTEIROS DOS ARQUIVOS DE ENTRADA E SAIDA  */

typedef struct
{
    FILE *arquivo_entrada;
    FILE *arquivo_saida;
    info_imagem *infoImagem;

} ponteiros_arquivos;

/* FUNCOES DA BIBLIOTECA */

void leitura_info(ponteiros_arquivos *input);
void escreve_info(ponteiros_arquivos *input);
void le_imagem(ponteiros_arquivos *input);
void escreve_imagem(ponteiros_arquivos *input );
