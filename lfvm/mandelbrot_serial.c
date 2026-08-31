#include "mandelbrot_common.h"

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