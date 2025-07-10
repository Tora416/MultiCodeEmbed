#include <stdio.h>

int main() {
    int x = 2, y, z = 4;
    printf("x = %d\nz = %d\n", x,z);
    printf("a) y = x++ + ++x => ");
    y = x++ + ++x;
    printf("%d\n", y);
    
    x = 2;
    printf("b) y = ++x + ++x => ");
    y = ++x + ++x;
    printf("%d\n", y);

    x = 2;
    printf("c) y = ++x + ++x + ++x => ");
    y = ++x + ++x + ++x; 
    printf("%d\n", y);
    
    x = 2;
    printf("d) y = x>z = ");
    y = x > z;
    printf("%d\n", y);
    
    printf("e) y = x>z?x:z = ");
    y = x > z ? x : z;
    printf("%d\n", y);

    return 0;
}
