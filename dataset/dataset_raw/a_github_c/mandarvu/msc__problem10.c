#include <stdio.h>

int main()
{
    int A[3][3],B[3][3],AB[3][3]={{0,0,0},{0,0,0},{0,0,0}};
    int ii,row,col;
    printf("Enter a 3*3 matrix A row wise.");

    for (ii = 0; ii < 3; ii++)
    {
        printf("\nRow %d >>> ",ii + 1);
        scanf("%d %d %d",(*(A + ii)+0),(*(A + ii)+1),(*(A +ii)+2));
    }
    printf("The matrix is A =\n\n");
    for (ii = 0;ii < 3; ii++)
        printf("\t%d\t%d\t%d\n",*(*(A + ii)+0),*(*(A + ii)+1),*(*(A +ii)+2));
    printf("Enter a 3*3 matrix B row wise.");

    for (ii = 0; ii < 3; ii++)
    {
        printf("\nRow %d >>> ",ii + 1);
        scanf("%d %d %d",(*(B + ii)+0),(*(B + ii)+1),(*(B +ii)+2));
    }
    printf("The matrix is B =\n\n");
    for (ii = 0;ii < 3; ii++)
        printf("\t%d\t%d\t%d\n",*(*(B + ii)+0),*(*(B + ii)+1),*(*(B +ii)+2));

    for (row=0;row<3;row++)
    {
        for (col=0;col<3;col++)
        {
            for (ii=0;ii<3;ii++)
            {
                *(*(AB+row)+col) += *(*(A+row)+ii) * *(*(B+ii)+col);
            }
        }
    }
    printf("The matrix is AB =\n\n");
    for (ii = 0;ii < 3; ii++)
        printf("\t%d\t%d\t%d\n",*(*(AB + ii)+0),*(*(AB + ii)+1),*(*(AB +ii)+2));
}
