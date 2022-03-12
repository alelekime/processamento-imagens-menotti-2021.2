// 20182558 ALESSANDRA SOUZA DA SILVA

#include "source/comando.h"
#include "source/processamento.h"
#include "source/acesso.h"

int main(int argc, char const *argv[])
{
    linha_comando *linhaComando = malloc(sizeof(linha_comando));
    ler_linha_comando(argc, argv, linhaComando);
    ponteiros_arquivos *input = malloc(sizeof(ponteiros_arquivos));

    if (!linhaComando->leitura_stdin)
        input->arquivo_entrada = abre_arquivo(linhaComando->entrada, true);
    else
        input->arquivo_entrada = stdin;
    input->infoImagem = malloc(sizeof(info_imagem));
    le_imagem(input);

    info_imagem *infoImagem = input->infoImagem;

    filtro_negativo(infoImagem->imagem, infoImagem->linhas, infoImagem->colunas, infoImagem->max_imagem);

    if (!linhaComando->impressao_stdin)
        input->arquivo_saida = abre_arquivo(linhaComando->saida, false);
    else
        input->arquivo_saida = stdout;
    escreve_imagem(input);

    free(linhaComando);
    libera_matriz(input->infoImagem->imagem, infoImagem->linhas);
    free(infoImagem);
    free(input);
    return 0;
}