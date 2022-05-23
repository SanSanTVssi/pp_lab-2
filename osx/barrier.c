//
//  barrier.c
//  PP_lab2
//
//  Created by AAI on 23.05.2022.
//

#include <pthread_barrier.h>

pthread_barrier_t barrier;

void* GetBarrierPointer() { return &barrier; }
