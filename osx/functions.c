//
//  functions.c
//  PP_lab2
//
//  Created by AAI on 23.05.2022.
//

#include "functions.h"
#include "barrier.h"
#include <pair.h>
#include <pthread_barrier.h>
#include <math.h>

double function1Result;
double function2Result;
double function3Result;

#define ArgsHandler(args) \
    pair pair_args = * (pair*) args; \
    pair boundaries = pair_first(pair, pair_args); \
    pair otherArgs = pair_second(pair, pair_args); \
    double a = pair_first(double, boundaries); \
    double b = pair_second(double, boundaries); \
    int n = pair_first(int, otherArgs); \
    double h = pair_second(double, otherArgs);

double CalculateX(double a, double h, double i) { return a + i * h; }

void *function1(void *args) {
    ArgsHandler(args)
    
    for (int i = 0; i <= n; i++) {
        double x = CalculateX(a, h, i);
        function1Result = powf(cosf(x), 2) + sinf(x);
        pthread_barrier_wait(pbarrier);
    }
    return 0;
}

void *function2(void *args) {
    ArgsHandler(args)

    for (int i = 0; i <= n; i++) {
        double x = CalculateX(a, h, i);
        function2Result = powf(sinf(x), 2) * (1 + cosf(x));
        pthread_barrier_wait(pbarrier);
    }
    return 0;
}

void *function3(void *args) {
    ArgsHandler(args)

    for (int i = 0; i <= n; i++) {
        double x = CalculateX(a, h, i);
        function3Result = sinf(x) * (1 + powf(cosf(x), 2));
        pthread_barrier_wait(pbarrier);
    }
    return 0;
}

double GetFunction1Result(void) { return function1Result; }
double GetFunction2Result(void) { return function2Result; }
double GetFunction3Result(void) { return function3Result; }
