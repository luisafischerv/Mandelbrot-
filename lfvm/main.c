#include <stdio.h>
#include <stdlib.h>
#define MAX_DIMENSAO 4000

long converter_argumento(char *texto, char *nome_parametro);

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Erro: numero incorreto de argumentos.\n");
        return 1;
    }
    
    long largura = converter_argumento(argv[1], "largura");
    if (largura <= 0 || largura > MAX_DIMENSAO) {
        fprintf(stderr, "Erro: largura deve ser um valor entre 1 e %d.\n", MAX_DIMENSAO);
        return 1;
    }
    long altura = converter_argumento(argv[2], "altura");
    if (altura <= 0 || altura > MAX_DIMENSAO) {
        fprintf(stderr, "Erro: altura deve ser um valor entre 1 e %d.\n", MAX_DIMENSAO);
        return 1;
    }
    long max_iteracoes = converter_argumento(argv[3], "max_iteracoes");
    if (max_iteracoes <= 0) {
        fprintf(stderr, "Erro: o numero maximo de interacoes deve ser maior que zero.\n");
        return 1;
    }
    long num_threads = converter_argumento(argv[4], "num_threads");
    if (num_threads <= 0) {
        fprintf(stderr, "Erro: o numero de threads deve ser maior que zero.\n");
        return 1;
    }

    return 0;
}

long converter_argumento(char *texto, char *nome_parametro) {
    char *fim;
    long valor = strtol(texto, &fim, 10);
    if (*fim != '\0') {
        fprintf(stderr, "Erro: %s invalido (nao e um numero): %s\n", nome_parametro, texto);
        exit(1);
    }
    return valor;
}