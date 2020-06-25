#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <mutex>

using namespace std;

struct signal
{
    int value = 0;
    bool written = false;
    bool read = true;
};

#define NUM_THREADS 100

int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;
int val5 = 0;
int val6 = 0;

void *thread_assign1(void *a)
{
    val2 = 2;
    return 0;
}

void *thread_assign2(void *a)
{
    val4 = 4;
    return 0;
}

void *thread_assign3(void *a)
{
    val5 = 5;
    return 0;
}

void *thread_assign4(void *a)
{
    val6 = 6;
    return 0;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int number_of_threads = 0;
    int non_blocking_index_begin = 0;
    int non_blocking_index_end = 0;
    
    val1 = 1;
 
    non_blocking_index_begin = number_of_threads;
    pthread_create (&threads [number_of_threads++], NULL, thread_assign1, NULL);
    pthread_create (&threads [number_of_threads++], NULL, thread_assign2, NULL);
    non_blocking_index_end = number_of_threads;

    for (int i = non_blocking_index_begin; i<non_blocking_index_end; i++){
        pthread_join(threads[i], NULL);
    }

    val3 =3;

    non_blocking_index_begin = number_of_threads;
    pthread_create (&threads [number_of_threads++], NULL, thread_assign3, NULL);
    pthread_create (&threads [number_of_threads++], NULL, thread_assign4, NULL);
    non_blocking_index_end = number_of_threads;

    for (int i = non_blocking_index_begin; i<non_blocking_index_end; i++){
        pthread_join(threads[i], NULL);
    }

    printf("val1 is: %d\n", val1);
    printf("val2 is: %d\n", val2);
    printf("val3 is: %d\n", val3);
    printf("val4 is: %d\n", val4);
    printf("val5 is: %d\n", val5);
    printf("val6 is: %d\n", val6);


}