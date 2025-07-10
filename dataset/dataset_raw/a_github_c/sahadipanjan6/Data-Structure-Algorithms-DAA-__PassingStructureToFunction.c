#include<stdio.h>
#include<string.h>


struct Book
{
    int book_id;
    float book_price;
    char book_name[100];
}b;


void displayBookDetails(struct Book b1);


void main()
{
    
    printf("\nEnter Book_ID: ");
    scanf("%d", &b.book_id);
    printf("\nEnter Book_Price: ");
    scanf("%f", &b.book_price);
    printf("\nEnter Book_Name: ");
    scanf("%s", &b.book_name);

    
    displayBookDetails(b);
}


void displayBookDetails(struct Book b1)
{
    
    printf("\nGetting the Book Details....\n");
    printf("\nBook_ID: %d", b1.book_id);
    printf("\nBook_Price: %f", b1.book_price);
    printf("\nBook_Name: %s", b1.book_name);
}