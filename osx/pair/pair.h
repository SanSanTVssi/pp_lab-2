//
// Created by Ааи on 07.02.2022.
//

#ifndef LAB1_PAIR_H
#define LAB1_PAIR_H

typedef struct PAIR {
    void* first;
    void* second;
} pair;

#define pair_set_values(val1, val2, pair) {\
    pair.first = (void*)&val1;                     \
    pair.second = (void*)&val2;     \
}      \

#define pair_set_first(val1, pair) { pair.first = (void*)&val1; }
#define pair_set_second(val2, pair) { pair.second = (void*)&val2; }

#define pair_first(type, target_pair) *(type*)target_pair.first
#define pair_second(type, target_pair) *(type*)target_pair.second

#endif //LAB1_PAIR_H
