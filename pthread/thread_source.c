#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* thread_func(void* arg) {
    while(1)
        sleep(1);
}


int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, NULL);
    pthread_t tid2;
    pthread_create(&tid2, NULL, thread_func, NULL);
    while(1) {
        sleep(1);
    }

    return 0;
}
