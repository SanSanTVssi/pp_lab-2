#include <math.h>
#include <stdio.h>
#include <pthread.h>
#include "pthread_barrier.h"
#include <unistd.h>

struct Data_params {
    float a;
    float b;
    int n;
    float h;
};

struct Data_result {
    float func1;
    float func2;
    float func3;
};

struct Data_result res;

pthread_barrier_t bar1;

void *func1(void *arg) {
    struct Data_params *p = (struct Data_params *) arg;

    float x;
    for (int j = 0; j <= p->n; j++) {
        x = p->a + ((float)j * p->h);
        res.func1 = powf(cosf(x), 2) + sinf(x);
        pthread_barrier_wait(&bar1);
    }
    return 0;
}

void *func2(void *arg) {
    struct Data_params *p = (struct Data_params *) arg;

    float x;
    for (int j = 0; j <= p->n; j++) {
        x = p->a + ((float)j * p->h);
        res.func2 = powf(sinf(x), 2) * (1 + cosf(x));
        pthread_barrier_wait(&bar1);
    }
    return 0;
}

void *func3(void *arg) {
    struct Data_params *p = (struct Data_params *) arg;

    float x;
    for (int j = 0; j <= p->n; j++) {
        x = p->a + ((float)j * p->h);
        res.func3 = sinf(x) * (1 + powf(cosf(x), 2));
        pthread_barrier_wait(&bar1);
    }
    return 0;
}

int main() {
    pthread_t pthread1;
    pthread_t pthread2;
    pthread_t pthread3;

    struct Data_params data_arg;

    data_arg.a = (float)-M_PI;
    data_arg.b = M_PI;
    data_arg.n = 8;
    data_arg.h = (data_arg.b - data_arg.a) / (float)data_arg.n;

    pthread_barrier_init(&bar1, NULL, 4);

    pthread_create(&pthread1, NULL, &func1, &data_arg);
    pthread_create(&pthread2, NULL, &func2, &data_arg);
    pthread_create(&pthread3, NULL, &func3, &data_arg);
    printf("=========================================================================================================\n");
    printf("| index |\t\tx\t\t|\tcos^2(x)+sin(x)\t\t|\tsin^2(x) * (1 + cos(x))\t|\tsin(x) * (1 + cos^2(x))\t|\n");
    printf("=========================================================================================================\n");
    for (int j = 0; j <= data_arg.n; j++) {
        float tmp_x = data_arg.a + ((float)j * data_arg.h);
        usleep(5000);
        printf("|\t%d\t|", j);
        (tmp_x < 0) ? printf("\t%f\t|", tmp_x) : printf("\t %f\t|", tmp_x);
        (res.func1 < 0) ? printf("\t\t%f\t\t|", res.func1) : printf("\t\t %f\t\t|", res.func1);
        (res.func2 < 0) ? printf("\t\t%f\t\t\t|", res.func2) : printf("\t\t %f\t\t\t|", res.func2);
        (res.func3 < 0) ? printf("\t\t%f\t\t\t|", res.func3) : printf("\t\t %f\t\t\t|", res.func3);
        printf("\n");
        pthread_barrier_wait(&bar1);
    }
    printf("=========================================================================================================\n");

    pthread_join(pthread1, NULL);
    pthread_join(pthread2, NULL);
    pthread_join(pthread3, NULL);

    pthread_barrier_destroy(&bar1);
    return 0;
}