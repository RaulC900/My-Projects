/*
    CREMENESCU RAUL-VALENTIN
    333CB
*/
#include "utils.h"

double* my_solver(int N, double *A, double* B) {

    int i, j, k;
    double *D = malloc(N * N * sizeof(double));
    double *final = malloc(N * N * sizeof(double));
    double *A_tr = malloc(N * N * sizeof(double));
    double *B_tr = malloc(N * N * sizeof(double));

    for (i = 0; i < N; ++i) {

        for ( j = 0; j < N; ++j) {

            A_tr[j * N + i] = A[i * N + j];
            B_tr[j * N + i] = B[i * N + j];
            D[i * N + j] = 0;
        }
    }

    for (i = 0; i < N; i++) {

        for (j = 0; j < N; j++) {

            double suma = 0.0;
            double suma1 = 0.0;

            if(i <= j) {
                for (k = 0; k < N; k++) {
                    suma += A_tr[i * N + k] * B[k * N + j];
                    suma1 += B_tr[i * N + k] * A[k * N + j];
                }

                D[i * N + j] = suma + suma1;
            }
        }
    }

    for (i = 0; i < N; i++) {

        for (j = 0; j < N; j++) {

            double sum = 0.0;
            for (k = 0; k < j + 1; k++) {

                    sum += D[i * N + k] * D[k * N + j];
            }
            final[i * N + j] = sum;
        }
    }

    free(D);
    free(A_tr);
    free(B_tr);

    return final;
}
