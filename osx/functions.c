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

float function1Result;
float function2Result;
float function3Result;

#define ArgsHandler(args) \
    pair pair_args = * (pair*) args; \
    pair boundaries = pair_first(pair, pair_args); \
    pair otherArgs = pair_second(pair, pair_args); \
    float a = pair_first(float, boundaries); \
    float b = pair_second(float, boundaries); \
    int n = pair_first(int, otherArgs); \
    float h = pair_second(float, otherArgs);

float CalculateX(float a, float h, float i) { return a + i * h; }

void *function1(void *args) {
    ArgsHandler(args)
    
    for (int i = 0; i <= n; i++) {
        float x = CalculateX(a, h, i);
        function1Result = powf(cosf(x), 2) + sinf(x);
        pthread_barrier_wait(GetBarrierPointer());
    }
    return 0;
}

void *function2(void *args) {
    ArgsHandler(args)

    for (int i = 0; i <= n; i++) {
        float x = CalculateX(a, h, i);
        function2Result = powf(sinf(x), 2) * (1 + cosf(x));
        pthread_barrier_wait(GetBarrierPointer());
    }
    return 0;
}

void *function3(void *args) {
    ArgsHandler(args)

    for (int i = 0; i <= n; i++) {
        float x = CalculateX(a, h, i);
        function3Result = sinf(x) * (1 + powf(cosf(x), 2));
        pthread_barrier_wait(GetBarrierPointer());
    }
    return 0;
}

float GetFunction1Result() { return function1Result; }
float GetFunction2Result() { return function2Result; }
float GetFunction3Result() { return function3Result; }
