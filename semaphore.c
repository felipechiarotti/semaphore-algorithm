#include <stdio.h>
#include <stdlib.h>

struct Semaphore{
    pthread_t *fila;
    int estado;
    int fila_size;
};

void semaphore_init(struct Semaphore s){
    s.fila = (pthread_t*) malloc(50 * sizeof(pthread_t))
    s.estado = 0;
    s.fila_size = -1;
}

// void upgrade_fila(struct Semaphore s){
//     s.fila = (pthread_t*) realloc(s.fila, 5 * sizeof(pthread_t));
// }

void lock(struct Semaphore s, pthread_t thread){
    s.fila_size++;
    pthread_t locked = s.fila[s.fila_size] = thread;
    while(locked != s.fila[0]);
    s.estado = 1;
}

void free_signal(struct Semaphore s){
    int i;
    if(s.fila_size > 0){
        for(i = 0; i < s.fila_size; i++){
            s.fila[i] = s.fila[i+1];
        }
    }else{
        s.fila[0] = NULL;
    }
    s.fila_size--;
    s.estado = 0;
}