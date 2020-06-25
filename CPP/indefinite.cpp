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

signal signal1;

void *thread_module_increment(void *a)
{
    while (true)
    {
        while (!signal1.read)
        {
        }

        signal1.value++;
        signal1.read = false;
        signal1.written = true;
    }
}

void *thread_module_print(void *a)
{
    while (true)
    {
        while (!signal1.written)
        {
        }

        int read_value = signal1.value;
        printf("value is read: %d\n", read_value);

        signal1.read = true;
        signal1.written = false;
    }
}

int main()
{

    pthread_t threads[NUM_THREADS];
    int number_of_threads = 0;
    pthread_create(&threads[number_of_threads++], NULL, thread_module_increment, NULL);
    pthread_create(&threads[number_of_threads++], NULL, thread_module_print, NULL);

    pthread_exit(NULL);
}
