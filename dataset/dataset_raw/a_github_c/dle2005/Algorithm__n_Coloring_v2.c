#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int n, m, **W, *vcolor;

bool promising(int i) {
    bool swtch = true;
    int j = 1;

    while(j < i && swtch) {
        if(W[i][j] && vcolor[i] == vcolor[j]) swtch = false;
        j++;
    }

    return swtch;
}

void m_coloring(int i) {
    
    for(int color = 1; color <= n; color++)
        printf("%d ", vcolor[color]);
    printf("\n");

    if(promising(i)) {
        if(i == n) {
            printf("volor = ");
            for(int color = 1; color <= n; color++)
                printf("%d ", vcolor[color]);
            printf("\n");
        }
        else {
            for(int color = 1; color <= m; color++) {
                vcolor[i+1] = color;
                m_coloring(i+1);
            }
        }
    }
}

void main() {
    printf("n = ");
    scanf("%d", &n);
    printf("m = ");
    scanf("%d", &m);
    printf("\n");

    W = (int **)malloc(sizeof(int *) * (n+1));
    for(int i = 0; i <= n; i++)
        W[i] = (int *)malloc(sizeof(int) * (n+1));
    vcolor = (int *)malloc(sizeof(int) * (n+1));
    memset(vcolor, 0, sizeof(int) * (n+1));

    printf("W = \n");
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            scanf("%d", &W[i][j]);
    printf("\n");

    m_coloring(0);
}

