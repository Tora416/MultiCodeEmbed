#include<stdio.h>

int main()
{
    int quantity_of_product;
    float unit_price, revenue,discount;
    printf("Enter quantity of product: ");
    scanf("%d",&quantity_of_product);
    printf("\nEnter the unit price: ");
    scanf("%f",&unit_price);
    revenue=quantity_of_product*unit_price;
    if(quantity_of_product>120 &&quantity_of_product<160)
    {
        discount=revenue*15/100;
        printf("\nDiscount : %f",discount);
        printf("\nAll payments : %f",(revenue-discount));
        
    }
    else if(quantity_of_product>160)
    {
        discount=revenue*20/100;
        printf("\nDiscount : %f",discount);
        printf("\nAll payments : %f",(revenue-discount));
        
    }
    else{
        discount=revenue*0/100;
        printf("\nDiscount : %f",discount);
        printf("\nAll payments : %f",(revenue-discount));
    }
}