#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mandelbrot_common.h"
#include "mandelbrot_serial.h"
#define MAX_DIMENSAO 4000

long converter_argumento(char *texto, char *nome_parametro);

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Erro: numero incorreto de argumentos.\n");
        return 1;
    }
    
    long largura = converter_argumento(argv[1], "largura");
    if (largura <= 1 || largura > MAX_DIMENSAO) {
        fprintf(stderr, "Erro: largura deve ser um valor entre 1 e %d.\n", MAX_DIMENSAO);
        return 1;
    }
    long altura = converter_argumento(argv[2], "altura");
    if (altura <= 1 || altura > MAX_DIMENSAO) {
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

    int **matriz = alocar_matriz(altura, largura);
    if (matriz == NULL) {
        fprintf(stderr, "Erro: falha ao alocar memoria para a matriz.\n");
        return 1;
    }
    struct timespec inicio;
    struct timespec fim;

    //serial
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    serial(matriz, largura, altura, max_iteracoes);
    clock_gettime(CLOCK_MONOTONIC, &fim);

    double tempo_serial = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    escrever_pgm("mandelbrot_lfvm_serial.pgm", matriz, largura, altura);

    //openmp
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    openmp(matriz, largura, altura, max_iteracoes, num_threads);
    clock_gettime(CLOCK_MONOTONIC, &fim);

    double tempo_openmp = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    escrever_pgm("mandelbrot_lfvm_openmp.pgm", matriz, largura, altura);

    //pthreads1
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    pthreads1(matriz, largura, altura, max_iteracoes, num_threads);
    clock_gettime(CLOCK_MONOTONIC, &fim);

    double tempo_pthreads1 = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    escrever_pgm("mandelbrot_lfvm_pthreads1.pgm", matriz, largura, altura);

    //pthreads2
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    pthreads2(matriz, largura, altura, max_iteracoes, num_threads);
    clock_gettime(CLOCK_MONOTONIC, &fim);

    double tempo_pthreads2 = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    escrever_pgm("mandelbrot_lfvm_pthreads2.pgm", matriz, largura, altura);

    FILE *arquivo_tempos = fopen("times.txt", "w");
    if (arquivo_tempos == NULL) {
        fprintf(stderr, "Erro: nao foi possivel criar times.txt\n");
        return 1;
    }
    fprintf(arquivo_tempos, "Serial: %.6f segundos\n", tempo_serial);
    fprintf(arquivo_tempos, "OpenMP: %.6f segundos\n", tempo_openmp);
    fprintf(arquivo_tempos, "Pthreads1: %.6f segundos\n", tempo_pthreads1);
    fprintf(arquivo_tempos, "Pthreads2: %.6f segundos\n", tempo_pthreads2);
    fclose(arquivo_tempos);

    liberar_matriz(matriz, altura);

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