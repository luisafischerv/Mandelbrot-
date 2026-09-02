#include <omp.h>
#include "mandelbrot_common.h"


void openmp(int **matriz, int largura, int altura, int max_interacoes, int num_threads) {
    omp_set_num_threads(num_threads);
    double c_real;
    double c_imag;
    int interacoes;

    #pragma omp parallel for
    for (int linha = 0; linha < altura; linha++) {
        for (int coluna = 0; coluna < largura; coluna++) {
            c_real = pixel_para_real(coluna, largura);
            c_imag = pixel_para_imag(linha, altura);
            interacoes = mandelbrot_ponto(c_real, c_imag, max_interacoes);
            matriz[linha][coluna] = normalizar_intensidade(interacoes, max_interacoes);
        }
    }
}