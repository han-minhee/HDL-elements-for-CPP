#include <iostream>
#include <cstdlib>
#include <pthread.h>

using namespace std;

struct signal
{
    int value = 0;
    bool written = false;
    bool read = true;
};

#define NUM_THREADS 100

signal signal_0;
signal signal_x;
signal signal_y;
signal signal_x_y;
 
void *thread_module1(void *a)
{
    int x = 1;
    int y = 2;
 
    while (!signal_x.read)
    {
    }
 
    signal_x.value = x;
    signal_x.read = false;
    signal_x.written = true;
 
    while (!signal_y.read)
    {
    }
 
    signal_y.value = y;
    signal_y.read = false;
    signal_y.written = true;
 
    return 0;
}
 
void *thread_module2(void *a)
{
    int x;
    int y;
 
    while (!signal_x.written)
    {
    }
    x = signal_x.value;
    signal_x.read = true;
    signal_x.written = false;
 
    while (!signal_y.written)
    {
    }
    y = signal_y.value;
    signal_y.read = true;
    signal_y.written = false;
    
    while (!signal_x_y.read)
    {
    }
 
    signal_x_y.value = x+y;
    signal_x_y.read = false;
    signal_x_y.written = true;
    
    return 0;
}

void *thread_module0 (void *a)
{
    pthread_t threads[NUM_THREADS];
    int number_of_threads = 0;
    pthread_create (&threads[number_of_threads++], NULL, thread_module1, NULL);
    pthread_create (&threads[number_of_threads++], NULL, thread_module2, NULL);
    
    int output;
    while (!signal_x_y.written)
    {
    }
 
    output = signal_x_y.value;
    signal_x_y.read = true;
    signal_x_y.written = false;

    while (!signal_0.read)
    {
    }
 
    signal_0.value = output;
    signal_0.read = false;
    signal_0.written = true;

    return 0;
}

void *thread_module_print(void *a)
{
    while (!signal_x_y.written)
    {
    }
    int read_value = signal_x_y.value;
    printf("value is read: %d\n", read_value);
    signal_x_y.read = true;
    signal_x_y.written = false;

    return 0;
}
 
 
int main(){
    pthread_t threads[NUM_THREADS];
    int number_of_threads = 0;
    pthread_create (&threads[number_of_threads++], NULL, thread_module0, NULL);
    pthread_create (&threads[number_of_threads++], NULL, thread_module_print, NULL);
    pthread_exit(NULL);
}
