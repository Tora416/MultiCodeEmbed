#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *filename = "num.txt";
    FILE *f = fopen(filename, "r");

    size_t num_ints = 0;
    for (char c = fgetc(f); c != EOF; c = fgetc(f)) {
        if (isdigit(c))
            num_ints++;
    }
    fclose(f);
    size_t *digits = calloc(sizeof(size_t), num_ints);
    f = fopen(filename, "r");
    for (size_t i = 0; i < num_ints; i++) {
        char c = fgetc(f);
        if (!isdigit(c))
            c = fgetc(f);
        digits[i] = c - '0';
    }
    size_t max_prod = 0;
    for (size_t i = 0; i < num_ints - 12; i++) {
        size_t tmp_prod = digits[i] * digits[i + 1] * digits[i + 2] * digits[i + 3]
                        * digits[i + 4] * digits[i + 5] * digits[i + 6] * digits[i + 7]
                        * digits[i + 8] * digits[i + 9] * digits[i + 10]
                        * digits[i + 11] * digits[i + 12];
        if (tmp_prod > max_prod)
            max_prod = tmp_prod;
    }
    printf("Answer: %zu\n", max_prod);
    free(digits);
    fclose(f);
    return 0;
}