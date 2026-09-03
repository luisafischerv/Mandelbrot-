#include <stdio.h>
#include <stdlib.h>
#include "mandelbrot_common.h"

int** alocar_matriz(int altura, int largura) {
    int **matriz = malloc(altura * sizeof(int *));
    if (matriz == NULL) {
        return NULL;
    }

    for (int i = 0; i < altura; i++) {
        matriz[i] = malloc(largura * sizeof(int));
        if (matriz[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matriz[j]);
            }
            free(matriz);
            return NULL;
        }
    }

    return matriz;
}

void liberar_matriz(int **matriz, int altura) {
    for (int i = 0; i < altura; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

int mandelbrot_ponto(double c_real, double c_imag, int max_iteracoes) {
    double z_real = 0.0;
    double z_imag = 0.0;
    for (int iteracao = 0; iteracao < max_iteracoes; iteracao++) {
        double z_real_novo = z_real * z_real - z_imag * z_imag + c_real;
        double z_imag_novo = 2 * z_real * z_imag + c_imag;
        z_real = z_real_novo;
        z_imag = z_imag_novo;
        if (z_real * z_real + z_imag * z_imag > 4.0) {
            return iteracao + 1;
        }
    }
    return max_iteracoes;
}

double pixel_para_real(int coluna, int largura) {
    return REAL_MIN + ((double)coluna / (largura)) * (REAL_MAX - REAL_MIN);
}

double pixel_para_imag(int linha, int altura) {
    return IMAG_MIN + ((double)linha / (altura)) * (IMAG_MAX - IMAG_MIN);
}

int normalizar_intensidade(int iteracoes, int max_iteracoes) {
    return (int) (((double)iteracoes / max_iteracoes) * 255.0);
}

void escrever_pgm(const char *nome_arquivo, int **matriz, int largura, int altura) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro: nao foi possivel criar o arquivo.\n");
        exit(1);
    }
    for (int linha = 0; linha < altura; linha++) {
        for (int coluna = 0; coluna < largura; coluna++) {
            fprintf(arquivo, "%d ", matriz[linha][coluna]);
        }
        fprintf(arquivo, "\n");
    }
    fclose(arquivo);
}

void mandelbrot_serial(int **matriz, int largura, int altura, int max_iteracoes) {
    for (int linha = 0; linha < altura; linha++) {
        for (int coluna = 0; coluna < largura; coluna++) {
            double c_real = pixel_para_real(coluna, largura);
            double c_imag = pixel_para_imag(linha, altura);

            int iteracoes = mandelbrot_ponto(c_real, c_imag, max_iteracoes);

            matriz[linha][coluna] = normalizar_intensidade(iteracoes, max_iteracoes);
        }
    }
}