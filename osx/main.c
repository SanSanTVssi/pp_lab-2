#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <pair.h>
#include <pthread_barrier.h>
#include "Constants.h"
#include "barrier.h"
#include "functions.h"

#define InitArgs(args) \
{ \
    pair boundaries; \
    pair_set_values(A, B, boundaries); \
    pair otherArgs; \
    pair_set_values(N, H, otherArgs); \
    pair_set_values(boundaries, otherArgs, args); \
}

int main() {
    pair args;
    InitArgs(args);

    pthread_t pthread1;
    pthread_t pthread2;
    pthread_t pthread3;
    pthread_barrier_init(pbarrier, NULL, 4);

    pthread_create(&pthread1, NULL,  &function1, &args);
    pthread_create(&pthread2, NULL,  &function2, &args);
    pthread_create(&pthread3, NULL,  &function3, &args);
    
    printf(
           "%s| i |%8s\t|%20s\t|%20s\t|%20s\t|\n%s",
           tableHorizontalLine,
           "x", FUNCTION1 ,FUNCTION2, FUNCTION3,
           tableHorizontalLine2
           );
    
    for (int i = 0; i <= N; i++) {
        double x = CalculateX(A, H, i);
        usleep(5000);
        printf("|%2d\t|", i);
        printf("%8.6f\t|", x);
        printf("%20.6f\t|", GetFunction1Result());
        printf("%20.6f\t|", GetFunction2Result());
        printf("%20.6f\t|\n", GetFunction3Result());
        pthread_barrier_wait(pbarrier);
    }
    
    printf(tableHorizontalLine2);

    pthread_join(pthread1, NULL);
    pthread_join(pthread2, NULL);
    pthread_join(pthread3, NULL);

    pthread_barrier_destroy(pbarrier);
    return 0;
}
