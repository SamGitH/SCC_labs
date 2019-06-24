#include <pthread.h>
#include <stdio.h>

double pi = 0;
int plusIter = 50000;

void *potok(void *param);
struct Iter {
        int iter = 0;
        double pi = 0;
};

double power(double x,double n){
    if(n == 0) return 1;
    if(n < 0) return power (1.0 / x, -n);
    return x * power(x, n - 1);
}

int main(int arg, char **args){

    int num = args[1][0] - 48;

    const int NUM_THREAD = num;
    printf("%d\n", NUM_THREAD);

    pthread_t tid[NUM_THREAD];
    pthread_attr_t attr;
    struct Iter it[NUM_THREAD];

    pthread_attr_init(&attr);

    for(int i = 0; i < NUM_THREAD; i++){
            it[i].iter = i * plusIter;
            pthread_create(&tid[i], &attr, potok,(void *)&it[i]);
    }

    for (int i = 0; i < NUM_THREAD; i++) {
            pthread_join(tid[i], NULL);
    }

    for (int i = 0; i < NUM_THREAD; i++) {
        pi += it[i].pi;
        printf("%f\n", pi);
    }
}



void *potok(void *param)
{
        struct Iter *it = (Iter *) param;
        double j = (double)it->iter;
        for(double i = 0; i < plusIter; i++)
        {
            it->pi += (1 / (power(16, (i+j))))*(4 / ((8 * (i+j)) + 1) - 2 / ((8 * (i+j)) + 4) - 1 / ((8 * (i+j)) + 5) - 1 / ((8 * (i+j)) + 6));
        }

        pthread_exit(0);
}

