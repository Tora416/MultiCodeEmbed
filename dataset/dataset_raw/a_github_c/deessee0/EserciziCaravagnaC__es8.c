

#include<stdio.h>
#include<stdlib.h>

struct triangolo {
  float beta; 
  float alfa;
  float gamma;
  int ab;
  int bc;
  int ac; 
};

typedef struct triangolo Triangolo;

float calcolo_perimetro(Triangolo* t)
{

    return  (t->ab + t->bc + t->ac);
}

void similitudine(Triangolo t1, Triangolo* t2)
{
    if((t1.alfa == t2->alfa) && (t1.beta == t2->beta) && (t1.gamma == t2->gamma))
    {
        printf("\n0 - l'equivalenza è vera");
    } else {
        printf("\n1 - l'equivalenza è falsa");
    }
    
}

int main() {

  Triangolo x1;
  Triangolo x2;



  printf("Inserire angolo alfa: ");
  scanf("%f", &x1.alfa);
  
  printf("Inserire angolo beta: ");
  scanf("%f", &x1.beta);

  printf("Inserire angolo gamma: ");
  scanf("%f", &x1.gamma);

  printf("Inserire lato AB: ");
  scanf("%d", &x1.ab);

  printf("Inserire lato BC: ");
  scanf("%d", &x1.bc);

  printf("Inserire lato AC: ");
  scanf("%d", &x1.ac);



  printf("Inserire angolo alfa: ");
  scanf("%f", &x2.alfa);
  
  printf("Inserire angolo beta: ");
  scanf("%f", &x2.beta);

  printf("Inserire angolo gamma: ");
  scanf("%f", &x2.gamma);

  printf("Inserire lato AB: ");
  scanf("%d", &x2.ab);

  printf("Inserire lato BC: ");
  scanf("%d", &x2.bc);

  printf("Inserire lato AC: ");
  scanf("%d", &x2.ac);


    float primo = calcolo_perimetro(&x1);
    float secondo = calcolo_perimetro(&x2);
    printf("primo: %f\nsecondo: %f", primo, secondo);
    similitudine(x1, &x2);
  

  return(0);
}
