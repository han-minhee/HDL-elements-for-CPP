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

signal signal_x;
signal signal_y;
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
 
    signal_y.value = x;
    signal_y.read = false;
    signal_y.written = true;
 
}
 
void *thread_module2(void *a)
{
    int x;
    int y;
 
    while (!signal_y.written)
    {
    }
    y = signal_y.value;
    signal_y.read = true;
    signal_y.written = false;
 
    while (!signal_y.written)
    {
    }
    x = signal_y.value;
    signal_y.read = true;
    signal_y.written = false;
    printf("%d\n", x+y);
}
 
int main(){
    pthread_t threads[NUM_THREADS];
    int number_of_threads = 0;
    pthread_create (&threads[number_of_threads++], NULL, module1, NULL);
    pthread_create (&threads[number_of_threads++], NULL, module2, NULL);
    pthread_exit(NULL);
}
