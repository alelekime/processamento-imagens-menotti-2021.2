
// 20182558 ALESSANDRA SOUZA DA SILVA

#include "source/comando.h"

/* LE A LINHA DE COMAND0*/
void ler_linha_comando(int argc, char const *argv[], linha_comando *linhaComando)
{

    int i;
    /* INCIALIZA COM TRUE AS VARIAVEIS QUE CONTROLA OS VALORES 
    DOS FILTROS PASSADOS PELA LINHA DE COMANDO */
    linhaComando->impressao_stdin = true;
    linhaComando->leitura_stdin = true;
    linhaComando->mascara = true;
    linhaComando->limiar = true;
    linhaComando->rotacao = true;
    /* PASSA POR TODOS OS ELEMENTOS DA LINHA DE COMANDO */
    for (i = 1; i < argc; i++) 
    {
        /* SE A POSICAO ATUAL FOR -i É ARQUIVO PARA LEITURA */
        if (!strcmp(argv[i], "-i"))
        {
            /* A LEITURA NAO SERA FEITA POR STDIN*/
            linhaComando->leitura_stdin = false;
            linhaComando->entrada = strdup(argv[i + 1]);
        }
        /* SE A POSICAO ATUAL FOR -o É ARQUIVO PARA ESCRITA */
        if (!strcmp(argv[i], "-o"))
        {
            /* A ESCRITA NAO SERA FEITA POR STDOUT */
            linhaComando->impressao_stdin = false;
            linhaComando->saida = strdup(argv[i + 1]);
        }
        /* SE A POSICAO ATUAL FOR -m É O VALOR DA MASCARA */
        if (!strcmp(argv[i], "-m"))
        {
            /* NAO É O VALOR PADRAO */
            linhaComando->mascara = false;
            sscanf(argv[i + 1], "%d", &linhaComando->valor_mascara);
        }
        /* SE A POSICAO ATUAL FOR -l É O VALOR DA LIMIAR */
        if (!strcmp(argv[i], "-l"))
        {
            /* NAO É O VALOR PADRAO */
            linhaComando->limiar = false;
            sscanf(argv[i + 1], "%lf", &linhaComando->valor_limiar);
            /* VERIFICA SE O LIMINAR ESTA NO LIMETE */
            if (linhaComando->valor_limiar > 1 || linhaComando->valor_limiar < 0)
            {
                fprintf(stderr, "LIMIAR %f FORA DOS LIMITES DEFINIDOS (ENTRE 0.0 E 1.0)\n", linhaComando->valor_limiar);
                exit(-1);
            }
        }
        /* SE A POSICAO ATUAL FOR -a É O VALOR DA ROTACAO */
        if (!strcmp(argv[i], "-a")) 
        {
            /*  NAO É O VALOR PADRAO */
            linhaComando->rotacao = false;
            sscanf(argv[i + 1], "%d", &linhaComando->valor_rotacao);
        }
    }
}
/* ABRE OS ARQUIVOS */
FILE *abre_arquivo(char *nome, bool entrada)
{
    FILE *arquivo;
    if (entrada)
        /* CASO FOR PARA LEITURA */
        arquivo = fopen(nome, "r");
    else
        /* CASO FOR ESCRITA */
        arquivo = fopen(nome, "w");

    /* VERIFICA SE DEU CERTO */
    if (arquivo == NULL)
    {
        printf("ERRO ARQUIVO %s: %s\n", nome, strerror(errno));
        exit(-1);
    }
    /* RETORNA O ARQUIVO */
    return arquivo;
}
