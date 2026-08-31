#include <stdlib.h>

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