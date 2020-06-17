/*
    CREMENESCU RAUL-VALENTIN
    333CB
*/
#include "utils.h"

double* my_solver(int N, double *A, double *B) {

        int i, j;
        double *aux;
        double *C = malloc(N * N * sizeof(double));
        aux = C;

        for (i = 0; i < N; ++i) {
                for ( j = 0; j < N; ++j) {
                        aux[i * N + j] = 0;
                }
        }

        cblas_dsyr2k(CblasRowMajor, CblasUpper, CblasTrans, N, N, 1.0, A, N, B, N, 0.0, C, N);
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1.0, C, N, C, N, 0.0, C, N);
        
        return C;
}

