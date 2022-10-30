#include "matrice_multithread.h" 

struct matrice_dot_thread_args {
    int i;
    int j;
    int n; // number of following fields to compute
    matrice *m1;
    matrice *m2;
    matrice *r;
};


void *matrice_dot_thread(void *args){
    struct matrice_dot_thread_args *arg = (struct matrice_dot_thread_args *) args;
    matrice *m1 = arg->m1;
    matrice *m2 = arg->m2;
    matrice *r = arg->r;
    int n = arg->n;

    for (int i = arg->i; i < r->rows && n > 0; i ++){
        for (int j = arg->j; j < r->columns && n > 0; j ++){
            double *sum = matrice_get_ref(r, i, j);
            *sum = 0;
            for (int k = 0; k < m1->columns; k ++){
                *sum += matrice_get(m1, i, k) * matrice_get(m2, k, j);
            }
            n --;
        }
    }
    return NULL;
}

void matrice_dot_mthreaded(matrice *m1, matrice *m2, matrice *r){
    int i, zAj;
    pthread_t threads[THREADS_COUNT];

    int thread_jobs = r->rows * r->columns / THREADS_COUNT;
    int thread_jobs_left = r->rows * r->columns % THREADS_COUNT;

    int job_i = 0;

    struct matrice_dot_thread_args **args_array = malloc(sizeof(struct matrice_dot_thread_args *) * THREADS_COUNT);

    for (i = 0; i < THREADS_COUNT; i ++){
        struct matrice_dot_thread_args *args = malloc(sizeof(struct matrice_dot_thread_args));
        args->i = job_i / r->columns;
        args->j = job_i % r->columns;
        args->n = thread_jobs;
        args->m1 = m1;
        args->m2 = m2;
        args->r = r;

        args_array[i] = args;

        if (thread_jobs_left > 0){
            args->n ++;
            thread_jobs_left --;
            job_i ++;
        }

        job_i += thread_jobs;

        pthread_create(&threads[i], NULL, matrice_dot_thread, args);
    }

    for (i = 0; i < THREADS_COUNT; i ++){
        pthread_join(threads[i], NULL);
    }

    for (i = 0; i < THREADS_COUNT; i ++){
        free(args_array[i]);
    }
    free(args_array);
}

    




