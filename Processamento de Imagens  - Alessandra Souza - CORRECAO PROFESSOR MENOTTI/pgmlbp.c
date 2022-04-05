// 20182558 ALESSANDRA SOUZA DA SILVA

#include "source/comando.h"
#include "source/processamento.h"
#include "source/acesso.h"

int main(int argc, char const *argv[])
{
    /* ALOCA UM PONTEIRO PARA A STRUCT QUE CUIDA DA LINHA DE COMANDO */
    linha_comando *linhaComando = malloc(sizeof(linha_comando));
    
    /* LE A LINHA DE COMANDO */
    ler_linha_comando(argc, argv, linhaComando);

    /* ALOCA UM PONTEIRO PARA A STRUCT QUE CUIDA DA IMAGEM */
    ponteiros_arquivos *input = malloc(sizeof(ponteiros_arquivos));

    /* VERIFICA SE A LEITURA É FEITA PELO STDIN OU ARQUIVO */
    if (!linhaComando->leitura_stdin)
        input->arquivo_entrada = abre_arquivo(linhaComando->entrada, true);
    else
        input->arquivo_entrada = stdin;

    /* ALOCA 0 PONTEIRO PARA A STRUCT QUE CUIDA DA DAS INFORMACOES DA IMAGEM*/
    input->infoImagem = malloc(sizeof(info_imagem));

    /* LE A IMAGEM */
    le_imagem(input);

    /* PONTEIRO AUXILIAR */
    info_imagem *infoImagem = input->infoImagem;

    /* APLICA O FILTRO LBP */
    // Menotti - retorno
    infoImagem->imagem = filtro_lbp(infoImagem->imagem, infoImagem->linhas, infoImagem->colunas);
    infoImagem->max_imagem = 255; // Menotti

    /* VERIFICA SE A ESCRITA É FEITA PELO STDOUT OU ARQUIVO */
    if (!linhaComando->impressao_stdin)
        input->arquivo_saida = abre_arquivo(linhaComando->saida, false);
    else
        input->arquivo_saida = stdout;
    /* ESCREVE A IMAGEM */
    escreve_imagem(input);

    /* LIBERA MATRIZ */
    libera_matriz(input->infoImagem->imagem, infoImagem->linhas);

    /* LIBERA TODOS OS PONTEIROS */
    free(linhaComando);
    free(input->infoImagem);
    free(input);
    return 0;
}
