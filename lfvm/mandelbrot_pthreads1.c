#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "mandelbrot_common.h"

typedef struct {
    int **matriz;
    int largura;
    int altura;
    int max_iteracoes;
    int linha_inicio;
    int linha_fim;
} DadosThread;

void* calcular_linhas(void *arg) {
    DadosThread *dados = (DadosThread *) arg;
    for (int linha = (dados->linha_inicio); linha < (dados->linha_fim); linha++) {
        for (int coluna = 0; coluna < dados->largura; coluna++) {
            double c_real = pixel_para_real(coluna, dados->largura);
            double c_imag = pixel_para_imag(linha, dados->altura);
            int iteracoes = mandelbrot_ponto(c_real, c_imag, dados->max_iteracoes);
            dados->matriz[linha][coluna] = normalizar_intensidade(iteracoes, dados->max_iteracoes);
        }
    }
    return NULL;
}

void pthreads1(int **matriz, int largura, int altura, int max_iteracoes, int num_threads) {
    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));
    DadosThread *dados = malloc(num_threads * sizeof(DadosThread));
    if (threads == NULL || dados == NULL) {
        fprintf(stderr, "Erro: falha ao alocar memoria para threads.\n");
        exit(1);
    }
    int linhas_por_thread = altura / num_threads;
    int resto = altura % num_threads;
    int linha_atual = 0;
    for (int t = 0; t < num_threads; t++) {
        int linhas_desta_thread;
        if (t < resto) linhas_desta_thread = linhas_por_thread + 1;
        else linhas_desta_thread = linhas_por_thread;
        dados[t].matriz = matriz;
        dados[t].largura = largura;
        dados[t].altura = altura;
        dados[t].max_iteracoes = max_iteracoes;
        dados[t].linha_inicio = linha_atual;
        dados[t].linha_fim = linha_atual + linhas_desta_thread;
        linha_atual += linhas_desta_thread;
        if (pthread_create(&threads[t], NULL, calcular_linhas, &dados[t]) != 0) {
            fprintf(stderr, "Erro: falha ao criar thread %d.\n", t);
            exit(1);
        }
    }

    for (int t = 0; t < num_threads; t++) {
        pthread_join(threads[t], NULL);
    }
    free(threads);
    free(dados);
}