#include <stdio.h>
void ft_print_combn(int n);

void comb1(int *numeros,int a);
void comb2(int *numeros,int a, int b);
void comb3(int *numeros,int a, int b,int c);
void comb4(int *numeros,int a, int b,int c,int d);  
void comb5(int *numeros,int a, int b,int c,int d,int e);
void comb6(int *numeros,int a, int b,int c,int d,int e,int f);
void comb7(int *numeros,int a, int b,int c,int d,int e,int f,int g);
void comb8(int *numeros,int a, int b,int c,int d,int e,int f,int g, int h);
void comb9(int *numeros,int a, int b,int c,int d,int e,int f,int g, int h, int i);

int main()
{
    ft_print_combn (2);
    return 0;
}

void ft_print_combn(int n)
{
    int numeros[10]={ 0, 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9}; 

    int a =0, b =1, c =2,d =3, e =4, f =5, g =6, h =7, i =8;    
    
    if(n==1)
      comb1(numeros,a);
      else{
           if(n==2)
              comb2(numeros,a,b);
              else{
                   if(n==3)
                     comb3(numeros,a,b,c);                      
                     else{
                          if(n==4)
                            comb4(numeros,a,b,c,d);
                            else{
                                 if(n==5)
                                   comb5(numeros,a,b,c,d,e);
                                   else{
                                        if(n==6)
                                          comb6(numeros,a,b,c,d,e,f);
                                          else{
                                               if(n==7)
                                                  comb7(numeros,a,b,c,d,e,f,g);
                                                  else{
                                                       if(n==8)
                                                          comb8(numeros,a,b,c,d,e,f,g,h);
                                                          else{
                                                               if(n==9)
                                                                  comb9(numeros,a,b,c,d,e,f,g,h,i);
                                                                  else{
                                                                       printf("Valor no procesable");
                                                                      }
                                                              }
                                                      }
                                              }
                                       }
                                }
                         }
                  }
          }  
}

void comb1(int *numeros,int a)
{
  while(a<=9)
       {
        printf("%i, ",numeros[a]); 
        a=a+1;
       }
}

void comb2(int *numeros,int a,int b)
{
  while(a<=8)
       {
        while(b<=9)
            {
              printf("%i%i, ",numeros[a],numeros[b]);    
              b=b+1;
            }
        a=a+1;
        b=a+1;
       }
}

void comb3(int *numeros,int a,int b,int c)
{
  while(a<=7)
       {
        while(b<=8)
             {
              while(c<=9)
                  {
                    printf("%i%i%i, ",numeros[a],numeros[b],numeros[c]);
                    c=c+1;
                  }
              b=b+1;
              c=b+1;
             }
        a=a+1;
        b=a+1;
        c=b+1;
       }
}

void comb4(int *numeros,int a,int b,int c, int d)
{
  while(a<=6)
       {
          while(b<=7)
               {
                while(c<=8)
                     {
                      while(d<=9)
                          {
                            printf("%i%i%i%i, ",numeros[a],numeros[b],numeros[c],numeros[d]);
                            d=d+1;
                          }
                      c=c+1;
                      d=c+1;
                     }     
                b=b+1;
                c=b+1;
                d=c+1;
               } 
          a=a+1;
          b=a+1;
          c=b+1;
          d=c+1;
       }
}

void comb5(int *numeros,int a,int b,int c, int d,int e)
{
  while(a<=5)
       {
          while(b<=6)
               {
                while(c<=7)
                    {
                      while(d<=8)
                           {
                            while(e<=9)
                                {
                                  printf("%i%i%i%i%i, ",numeros[a],numeros[b],numeros[c],numeros[d],numeros[e]);
                                  e=e+1;
                                }
                            d=d+1;
                            e=d+1;
                           }
                      c=c+1;
                      d=c+1;
                      e=d+1;
                    }
                b=b+1;
                c=b+1;
                d=c+1;
                e=d+1;
               } 
          a=a+1;
          b=a+1;
          c=b+1;
          d=c+1;
          e=d+1;
       }
}

void comb6(int *numeros,int a,int b,int c, int d,int e,int f)
{
  while(a<=4)
       {
          while(b<=5)
              {
                  while(c<=6)
                      {
                        while(d<=7)
                            {
                              while(e<=8)
                                   {
                                    while(f<=9)
                                        {
                                          printf("%i%i%i%i%i%i, ",numeros[a],numeros[b],numeros[c],numeros[d],numeros[e],numeros[f]);
                                          f=f+1;
                                        }
                                    e=e+1;
                                    f=e+1;
                                   }
                              d=d+1;
                              e=d+1;
                              f=e+1;
                            }
                        c=c+1;
                        d=c+1;
                        e=d+1;
                        f=e+1;
                      } 
                  b=b+1;
                  c=b+1;
                  d=c+1;
                  e=d+1;
                  f=e+1;
              }
          a=a+1;
          b=a+1;
          c=b+1;
          d=c+1;
          e=d+1;
          f=e+1;
      }
}

void comb7(int *numeros,int a,int b,int c, int d,int e,int f,int g)
{
  while(a<=3)
       {
        while(b<=4)
            {
                while(c<=5)
                    {
                        while(d<=6)
                            {
                              while(e<=7)
                                  {
                                    while(f<=8)
                                         {
                                          while(g<=9)
                                              {
                                                printf("%i%i%i%i%i%i%i, ",numeros[a],numeros[b],numeros[c],numeros[d],numeros[e],numeros[f],numeros[g]);
                                                g=g+1;
                                              }
                                          f=f+1;
                                          g=f+1;
                                         }
                                    e=e+1;
                                    f=e+1;
                                    g=f+1;
                                  }
                              d=d+1;
                              e=d+1;
                              f=e+1;
                              g=f+1;
                            } 
                        c=c+1;
                        d=c+1;
                        e=d+1;
                        f=e+1;
                        g=f+1;
                    }
                b=b+1;
                c=b+1;
                d=c+1;
                e=d+1;
                f=e+1;
                g=f+1;
            }
        a=a+1;
        b=a+1;
        c=b+1;
        d=c+1;
        e=d+1;
        f=e+1;
        g=f+1;
       }
}

void comb8(int *numeros,int a,int b,int c, int d,int e,int f,int g,int h)
{
  while(a<=2)
       {
        while(b<=3)
            {
              while(c<=4)
                  {
                      while(d<=5)
                          {
                              while(e<=6)
                                  {
                                    while(f<=7)
                                        {
                                          while(g<=8)
                                               {
                                                while(h<=9)
                                                    {
                                                      printf("%i%i%i%i%i%i%i%i, ",numeros[a],numeros[b],numeros[c],numeros[d],numeros[e],numeros[f],numeros[g],numeros[h]);
                                                      h=h+1;
                                                    }
                                                g=g+1;
                                                h=g+1;
                                               }
                                          f=f+1;
                                          g=f+1;
                                          h=g+1;
                                        }
                                    e=e+1;
                                    f=e+1;
                                    g=f+1;
                                    h=g+1;
                                  } 
                              d=d+1;
                              e=d+1;
                              f=e+1;
                              g=f+1;
                              h=g+1;
                          }
                      c=c+1;
                      d=c+1;
                      e=d+1;
                      f=e+1;
                      g=f+1;
                      h=g+1;
                  }
              b=b+1;
              c=b+1;
              d=c+1;
              e=d+1;
              f=e+1;
              g=f+1;
              h=g+1;
            }
        a=a+1;
        b=a+1;
        c=b+1;
        d=c+1;
        e=d+1;
        f=e+1;
        g=f+1;
        h=g+1;
       }
}

void comb9(int *numeros,int a,int b,int c, int d,int e,int f,int g,int h,int i)
{
  while(a<=1)
       {
        while(b<=2)
            {
              while(c<=3)
                  {
                    while(d<=4)
                        {
                            while(e<=5)
                                {
                                    while(f<=6)
                                        {
                                          while(g<=7)
                                              {
                                                while(h<=8)
                                                     {
                                                      while(i<=9)
                                                          {
                                                            printf("%i%i%i%i%i%i%i%i%i, ",numeros[a],numeros[b],numeros[c],numeros[d],numeros[e],numeros[f],numeros[g],numeros[h],numeros[i]);
                                                            i=i+1;
                                                          }
                                                      h=h+1;
                                                      i=h+1;
                                                     }
                                                g=g+1;
                                                h=g+1;
                                                i=h+1;
                                              }
                                          f=f+1;
                                          g=f+1;
                                          h=g+1;
                                          i=h+1;
                                        } 
                                    e=e+1;
                                    f=e+1;
                                    g=f+1;
                                    h=g+1;
                                    i=h+1;
                                }
                            d=d+1;
                            e=d+1;
                            f=e+1;
                            g=f+1;
                            h=g+1;
                            i=h+1;
                        }
                    c=c+1;
                    d=c+1;
                    e=d+1;
                    f=e+1;
                    g=f+1;
                    h=g+1;
                    i=h+1;
                  }
              b=b+1;
              c=b+1;
              d=c+1;
              e=d+1;
              f=e+1;
              g=f+1;
              h=g+1;
              i=h+1;
            }
        a=a+1;
        b=a+1;
        c=b+1;
        d=c+1;
        e=d+1;
        f=e+1;
        g=f+1;
        h=g+1;
        i=h+1;
       }
}