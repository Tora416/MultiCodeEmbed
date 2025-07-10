#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

int num_digits(size_t i) {
    if (i < 10) return 1;
    return 1 + num_digits(i / 10);
}

int power(size_t x, size_t y) {
    if (y == 0) return 1;
    return x * pow(x, y - 1);
}

bool is_palin(size_t i, size_t num_digits) {
    if (num_digits < 2) return true;
    return i % 10 == i / power(10, num_digits - 1)
        && is_palin((i % power(10, num_digits - 1)) / 10, num_digits - 2);
}

int main() {
    size_t max_palin = 0;
    for (size_t i = 100; i < 1000; i++)
        for (size_t j = i; j < 1000; j++)
            if (is_palin(i * j, num_digits(i * j)) && i * j > max_palin)
                max_palin = i * j;
    printf("Answer: %zu\n", max_palin);
    return 0;
}