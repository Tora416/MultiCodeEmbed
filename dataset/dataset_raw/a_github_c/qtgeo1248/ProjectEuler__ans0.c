#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *filename = "num.txt";
    FILE *f = fopen(filename, "r");
    char *line = NULL; size_t len = 0; char *thing = NULL;
    getline(&line, &len, f);
    
    size_t max = strtol(line, &thing, 10);
    size_t *primes = calloc(sizeof(size_t), max / 4);
    size_t num = 0;
    for (size_t test = 2; test < max; test++) {
        bool isPrime = true;
        for (size_t i = 0; i < num; i++) {
            if (test % primes[i] == 0)
                isPrime = false;
        }
        if (isPrime) {
            primes[num] = test;
            num++;
        }
    }
    
    size_t sum = 0;
    for (size_t i = 0; i < num; i++)
        sum += primes[i];
    printf("Answer: %zu\n", sum);
    free(primes);
    fclose(f);
    free(line);
    return 0;
}