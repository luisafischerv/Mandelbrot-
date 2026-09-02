#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "mandelbrot_common.h"

typedef struct {
    int **matriz;
    int largura;
    int altura;
    int max_iteracoes;
    int *proxima_linha;
    pthread_mutex_t *mutex;
} DadosThread2;

void* calcular_linhas_dinamico(void *arg) {
    DadosThread2 *dados = (DadosThread2 *) arg;

    pthread_mutex_lock(dados->mutex);
    while (1) {
        int linha = *(dados->proxima_linha);
        *(dados->proxima_linha) = linha + 1;
        pthread_mutex_unlock(dados->mutex);
        
        if (linha >= dados->altura) {
            break;
        }
        
        for (int coluna = 0; coluna < dados->largura; coluna++) {
            double c_real = pixel_para_real(coluna, dados->largura);
            double c_imag = pixel_para_imag(linha, dados->altura);
            int iteracoes = mandelbrot_ponto(c_real, c_imag, dados->max_iteracoes);
            dados->matriz[linha][coluna] = normalizar_intensidade(iteracoes, dados->max_iteracoes);
        }
    }

    return NULL;
}

void pthreads2(int **matriz, int largura, int altura, int max_iteracoes, int num_threads) {
    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));
    DadosThread2 *dados = malloc(num_threads * sizeof(DadosThread2));

    if (threads == NULL || dados == NULL) {
        fprintf(stderr, "Erro: falha ao alocar memoria para threads.\n");
        exit(1);
    }

    int proxima_linha = 0;
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    for (int t = 0; t < num_threads; t++) {
        dados[t].matriz = matriz;
        dados[t].largura = largura;
        dados[t].altura = altura;
        dados[t].max_iteracoes = max_iteracoes;
        dados[t].proxima_linha = &proxima_linha;
        dados[t].mutex = &mutex;

        if (pthread_create(&threads[t], NULL, calcular_linhas_dinamico, &dados[t]) != 0) {
            fprintf(stderr, "Erro: falha ao criar thread %d.\n", t);
            exit(1);
        }
    }

    for (int t = 0; t < num_threads; t++) {
        pthread_join(threads[t], NULL);
    }

    pthread_mutex_destroy(&mutex);
    free(threads);
    free(dados);
}