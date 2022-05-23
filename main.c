/*
    КВ-03 Жовтанюк Максим
    Варіант - 7
    a = -M_PI
    b = M_PI
    n = 8
    функції: 2, 5, 11
    cos^2(x) + sin(x)
    sin^2(x) * (1 + cos(x))
    sin(x) * (1 + cos^2(x))
*/

#include <math.h> // для математичних обчислень
#include <stdio.h> // для виводу
#include <pthread.h> // для потоків та бар'єрів
#include <unistd.h> // для usleep()

struct Data_params {
    float a;
    float b;
    int n;
    float h;
};
struct Data_params data_arg;
// структура та її об'єкт для передавання параметра у потік

struct Data_result {
    float func1;
    float func2;
    float func3;
};
struct Data_result res;
// структура та її об'єкт для визначення результатів обчислення для кожного потоку

pthread_barrier_t bar1; // оголошення бар'єру

// функції для виконання у відповідних потоках
void *func1(void *arg);
void *func2(void *arg);
void *func3(void *arg);

int main() {
    pthread_t pthread1;
    pthread_t pthread2;
    pthread_t pthread3;
    // оголошення потоків

    data_arg.a = (float)-M_PI;
    data_arg.b = M_PI;
    data_arg.n = 8;
    data_arg.h = (data_arg.b - data_arg.a) / (float)data_arg.n;
    // ініціалізація об'єкту структури для передавання параметра у потокі

    //ініціаліція бар'єру
    pthread_barrier_init(&bar1, NULL, 4);

    // створення потоків
    pthread_create(&pthread1, NULL, &func1, &data_arg);
    pthread_create(&pthread2, NULL, &func2, &data_arg);
    pthread_create(&pthread3, NULL, &func3, &data_arg);

    // вивід заголовку таблиці
    printf("=========================================================================================================================================\n");
    printf("|\tindex\t|\tx\t\t|\tcos^2(x)+sin(x)\t\t|\tsin^2(x) * (1 + cos(x))\t|\tsin(x) * (1 + cos^2(x))\t|\n");
    printf("=========================================================================================================================================\n");

    // цикл для виводу результатів обчислення потоків
    for (int j = 0; j <= data_arg.n; j++) {
        float tmp_x = data_arg.a + ((float)j * data_arg.h);
        usleep(5000); // затримка для синхронізації
        printf("|\t%d\t|", j);
        (tmp_x < 0) ? printf("\t%f\t|", tmp_x) : printf("\t %f\t|", tmp_x);
        (res.func1 < 0) ? printf("\t%f\t\t|", res.func1) : printf("\t %f\t\t|", res.func1);
        (res.func2 < 0) ? printf("\t%f\t\t|", res.func2) : printf("\t %f\t\t|", res.func2);
        (res.func3 < 0) ? printf("\t%f\t\t|", res.func3) : printf("\t %f\t\t|", res.func3);
        printf("\n");
        pthread_barrier_wait(&bar1); // очікування бар'єру
    }

    printf("=========================================================================================================================================\n");

    // очікування завершення роботи потоків
    pthread_join(pthread1, NULL);
    pthread_join(pthread2, NULL);
    pthread_join(pthread3, NULL);

    // знищення бар'єра
    pthread_barrier_destroy(&bar1);
    return 0;
}

void *func1(void *arg) {
    // приведення безтипового параметра до вказівника на об'єкт структури
    struct Data_params *p = (struct Data_params *) arg;

    float x;
    for (int j = 0; j <= p->n; j++) {
        x = p->a + ((float)j * p->h);
        res.func1 = powf(cosf(x), 2) + sinf(x);
        pthread_barrier_wait(&bar1); // очікування бар'єра
    }
    return 0;
}

void *func2(void *arg) {
    // приведення безтипового параметра до вказівника на об'єкт структури
    struct Data_params *p = (struct Data_params *) arg;

    float x;
    for (int j = 0; j <= p->n; j++) {
        x = p->a + ((float)j * p->h);
        res.func2 = powf(sinf(x), 2) * (1 + cosf(x));
        pthread_barrier_wait(&bar1); // очікування бар'єра
    }
    return 0;
}

void *func3(void *arg) {
    // приведення безтипового параметра до вказівника на об'єкт структури
    struct Data_params *p = (struct Data_params *) arg;

    float x;
    for (int j = 0; j <= p->n; j++) {
        x = p->a + ((float)j * p->h);
        res.func3 = sinf(x) * (1 + powf(cosf(x), 2));
        pthread_barrier_wait(&bar1); // очікування бар'єра
    }
    return 0;
}
