
// 20182558 ALESSANDRA SOUZA DA SILVA

#include "source/comando.h"

void ler_linha_comando(int argc, char const *argv[], linha_comando *linhaComando)
{

    int i;
    linhaComando->impressao_stdin = true;
    linhaComando->leitura_stdin = true;
    linhaComando->mascara = true;
    linhaComando->limiar = true;
    linhaComando->rotacao = true;

    for (i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-i"))
        {
            linhaComando->leitura_stdin = false;
            linhaComando->entrada = strdup(argv[i + 1]);
        }

        if (!strcmp(argv[i], "-o"))
        {
            linhaComando->impressao_stdin = false;
            linhaComando->saida = strdup(argv[i + 1]);
        }

        if (!strcmp(argv[i], "-m"))
        {
            linhaComando->mascara = false;
            sscanf(argv[i + 1], "%d", &linhaComando->valor_mascara);
        }

        if (!strcmp(argv[i], "-l"))
        {
            linhaComando->limiar = false;
            sscanf(argv[i + 1], "%lf", &linhaComando->valor_limiar);
            if (linhaComando->valor_limiar > 1 || linhaComando->valor_limiar < 0)
            {
                fprintf(stderr, "LIMIAR %f FORA DOS LIMITES DEFINIDOS (ENTRE 0.0 E 1.0)\n", linhaComando->valor_limiar);
                exit(-1);
            }
        }
        

        if (!strcmp(argv[i], "-a"))
        {
            linhaComando->rotacao = false;
            sscanf(argv[i + 1], "%d", &linhaComando->valor_rotacao);
        }
    }
}

FILE *abre_arquivo(char *nome, bool entrada)
{
    FILE *arquivo;
    if (entrada)
        arquivo = fopen(nome, "r");
    else
        arquivo = fopen(nome, "w");

    if (arquivo == NULL)
    {
        printf("ERRO ARQUIVO %s: %s\n", nome, strerror(errno));
        exit(-1);
    }
    return arquivo;
}
