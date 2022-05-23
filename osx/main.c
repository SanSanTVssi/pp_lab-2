#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <pair.h>
#include <pthread_barrier.h>
#include "Constants.h"
#include "barrier.h"
#include "functions.h"

#define InitArgs \
pair boundaries; \
pair_set_values(A, B, boundaries); \
pair otherArgs; \
pair_set_values(N, H, otherArgs); \
pair args; \
pair_set_values(boundaries, otherArgs, args);

int main() {
    InitArgs

    pthread_t pthread1;
    pthread_t pthread2;
    pthread_t pthread3;
    pthread_barrier_init(GetBarrierPointer(), NULL, 4);

    pthread_create(&pthread1, NULL,  &function1, &args);
    pthread_create(&pthread2, NULL,  &function2, &args);
    pthread_create(&pthread3, NULL,  &function3, &args);
    
    printf("| index %4|\t\tx\t\t|\tcos^2(x)+sin(x)\t| sin^2(x)*(1+cos(x))\t|sin(x)*(1+cos^2(x))|\n %s",
           "_____________________________________________________________________________\n");
    for (int i = 0; i <= N; i++) {
        float x = CalculateX(A, H, i);
        usleep(5000);
        printf("|%8d\t|", i);
        printf("%16.6f\t|", x);
        printf("%24.6f\t|", GetFunction1Result());
        printf("%24.6f\t|", GetFunction2Result());
        printf("%24.6f\t|", GetFunction3Result());
        printf("\n");
        pthread_barrier_wait(GetBarrierPointer());
    }

    pthread_join(pthread1, NULL);
    pthread_join(pthread2, NULL);
    pthread_join(pthread3, NULL);

    pthread_barrier_destroy(GetBarrierPointer());
    return 0;
}
