/*
    CREMENESCU RAUL-VALENTIN
    333CB
*/
#include "utils.h"

double* my_solver(int N, double *A, double* B) {

    int i, j;
    register int k;
    double *D = malloc(N * N * sizeof(double));
    double *final = malloc(N * N * sizeof(double));
    double *A_tr = malloc(N * N * sizeof(double));
    double *B_tr = malloc(N * N * sizeof(double));
    double *D_tr = malloc(N * N * sizeof(double));

    for(i = 0; i < N; i++) {

        double *p1 = &A[i * N];
        double *p2 = &B[i * N];
        double *p3 = &D[i * N];
        double *p4 = &final[i * N];
        double *p5 = &D_tr[i * N];

        for(j = 0; j < N; j++) {

            A_tr[j * N + i] = *p1;
            B_tr[j * N + i] = *p2;
            p1++;
            p2++; 
            *p3 = 0;
            p3++;
            *p4 = 0;
            p4++;
            *p5 = 0;
            p5++;
        }
    }

    for (i = 0; i < N; i++) {

        double *orig_pa_tr = &A_tr[i * N];
        double *orig_pb_tr = &B_tr[i * N];
        double *d = &D[i * N];
        double *pa_tr1 = &A_tr[i * N];
        double *pb_tr1 = &B_tr[i * N];
        double *aux = &D_tr[i];

        for (j = 0; j < N; j++) {

            double *pa_tr = orig_pa_tr;
            double *pb_tr = orig_pb_tr;
            register double suma = 0.0;

            if(i <= j) {
                for (k = 0; k < N; k++) {

                    suma += (*pa_tr * *pb_tr1) + (*pb_tr * *pa_tr1);
                    pa_tr++;
                    pa_tr1++;
                    pb_tr++;
                    pb_tr1++;

                }
                *d = suma;
                *aux = suma;
            }

            d++;
            aux += N;
            double *pa_tr1 = &A_tr[i * N];
            double *pb_tr1 = &B_tr[i * N];
            pa_tr1 += N;
            pb_tr1 += N;

        }
        d += N;
    }

    for (i = 0; i < N; i++) {

        double *orig_d = &D[i * N];
        double *f = &final[i * N];
        double *d_tr = &D_tr[i * N];

        for (j = 0; j < N; j++) {

            double *d = orig_d;
            register double sum = 0.0;

            if(i <= j) {

                for (k = 0; k < N; k++) {
                        sum += *d * *d_tr;
                        d++;
                        d_tr++;
                }
                *f = sum;
            }

            f++;
            double *d_tr = &D_tr[i * N];
            d_tr += N;
            
        }
        f += N;
    }

    free(D);
    free(A_tr);
    free(B_tr);
    free(D_tr);

    return final;
}