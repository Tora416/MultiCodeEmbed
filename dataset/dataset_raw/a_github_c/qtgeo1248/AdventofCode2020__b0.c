#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main() {
    char *filename = "Passwords.txt";
    FILE *f = fopen(filename, "r");
    char *line = NULL;
    size_t n = 0;
    size_t valids = 0;
    while (getline(&line, &n, f) != -1) {
        char *str = strchr(line, ':');
        char *pass = calloc(sizeof(char), strlen(str) - 2);
        strcpy(pass, &str[2]);
        int i = strtol(line, &line, 10);
        line++;
        int j = strtol(line, &line, 10);
        char c = line[1];
        
        if ((pass[i - 1] == c || pass[j - 1] == c) && pass[i - 1] != pass[j - 1])
            valids++;

        free(pass);
    }

    printf("Answer: %zu\n", valids);
    fclose(f);

    return 0;
}