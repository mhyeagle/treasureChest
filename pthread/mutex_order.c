//互斥锁加锁后，其他加互斥锁的线程会按照先后顺序排成队列

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex__;
int sleep_time = 1;

static void* thread_func(void* arg) {
    int t_num = (int)arg;
    printf("thread %d created\n", t_num);
    pthread_mutex_lock(&mutex__);
    printf("thread %d get mutex lock, and will sleep %d seconds\n", t_num, sleep_time);
    sleep(sleep_time);
    sleep_time += 2;
    printf("thread %d release mutex lock\n", t_num);
    pthread_mutex_unlock(&mutex__);
}

int main() {
    pthread_t tid[3];

    printf("main thread get mutex\n");
    pthread_mutex_lock(&mutex__);

    for(int i = 0; i < 3; ++i) {
        pthread_create(&tid[i], NULL, thread_func, i);
    }

    printf("main thread sleep 1 second\n");
    sleep(1);

    pthread_mutex_unlock(&mutex__);

    printf("main thread sleep 10 second\n");
    sleep(10);
    

    return 0;
}
