#ifndef MANDELBROT_COMMON_H
#define MANDELBROT_COMMON_H
#define REAL_MIN -2.0
#define REAL_MAX  1.0
#define IMAG_MIN -1.5
#define IMAG_MAX  1.5

int** alocar_matriz(int altura, int largura);
void liberar_matriz(int **matriz, int altura);
int mandelbrot_ponto(double c_real, double c_imag, int max_iteracoes);
double pixel_para_real(int coluna, int largura);
double pixel_para_imag(int linha, int altura);
int normalizar_intensidade(int iteracoes, int max_iteracoes);
void escrever_pgm(const char *nome_arquivo, int **matriz, int largura, int altura);
void mandelbrot_serial(int **matriz, int largura, int altura, int max_iteracoes);

#endif