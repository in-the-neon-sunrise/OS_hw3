#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    unsigned long long n;
    sscanf(argv[1], "%llu", &n); // считывание аргумента из командной строки
    pid_t chpid;
    chpid = fork(); // создание процесса-ребенка
    if(chpid <= -1) {
        printf("Incorrect fork syscall\n");
    } else if (chpid == 0) { // проверка, в каком процессе мы находимся
        printf("Factorial: ");
        // вычисление факториала в процессе-ребенке
        unsigned long long fact = 1;
        unsigned long long prev_fact = 1;
        for (unsigned long long i = 1; i <= n; ++i) {
            prev_fact = fact;
            fact *= i;
            if (fact < prev_fact) { // проверка на переполнение
                printf("Overflow :<\n");
                exit(1);
            }
        }
        printf("%llu\n", fact);
        exit(0); // завершение процесса
    } else {
        printf("Fibonacci: ");
        // вычисление числа Фибоначчи в процессе-родителе
        unsigned long long fib = 1;
        unsigned long long prev_fib = 1;
        for (unsigned long long i = 1; i <= n; ++i) {
            unsigned long long prev_fib1 = prev_fib;
            prev_fib = fib;
            fib = prev_fib + prev_fib1;
            if (fib < prev_fib) { // проверка на переполнение
                printf("Overflow :<\n");
                exit(1);
            }
        }
        printf("%llu\n", fib);
        exit(0); // завершение процесса
    }
}