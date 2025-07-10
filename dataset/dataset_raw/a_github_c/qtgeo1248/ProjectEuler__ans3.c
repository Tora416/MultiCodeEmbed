#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

int main() {
    char *filename = "num.txt";
    FILE *f = fopen(filename, "r");
    char *line = NULL; size_t len = 0; char *tmp = NULL;
    getline(&line, &len, f);
    size_t p = strtol(line, &tmp, 10);
    size_t size = ceil(sqrt(p));
    bool *primes = calloc(sizeof(bool), size + 1); 

    for (size_t i = 2; i < size + 1; i++) {
        if (!primes[i])
            for (size_t j = 2 * i; j < size + 1; j += i)
                primes[j] = true;
    }
    size_t maxp = 0;
    for (size_t i = 2; i < size + 1; i++) {
        if (!primes[i] && p % i == 0 && i > maxp)
            maxp = i;
    }
    printf("Answer: %zu\n", maxp);
    free(primes);
    fclose(f); free(line);
    return 0;
}