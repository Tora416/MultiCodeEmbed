#include <limits.h>

int raise(int b, int n);
long l_raise(int base, int n);
void main(){
  printf("\n");
  printf("Range values from standard headers:\n");
  printf("\t -Signed-\n");
  printf("char  : [%d, %d]\n", CHAR_MIN, CHAR_MAX);
  printf("short : [%d, %d]\n", SHRT_MIN, SHRT_MAX);
  printf("int   : [%d, %d]\n", INT_MIN, INT_MAX);
  printf("long  : [%ld, %ld]\n\n", LONG_MIN, LONG_MAX);
  printf("\t -Unsigned-\n");
  printf("char  : [0, %d]\n", UCHAR_MAX);
  printf("short : [0, %d]\n", USHRT_MAX);
  printf("int   : [0, %u]\n", UINT_MAX);
  printf("long  : [0, %lu]\n", ULONG_MAX);
  printf("\n");
  
  printf("Range values by direct computation:\n");
  printf("\t -Signed-\n");
  printf("char  : [-%d, %d]\n", raise(2, sizeof(char)*CHAR_BIT - 1 ) ,
     raise(2, sizeof(char)*CHAR_BIT - 1) - 1);
  
  printf("short : [-%d, %d]\n", raise(2, sizeof(short)*CHAR_BIT - 1 ) ,
     raise(2, sizeof(short)*CHAR_BIT - 1) - 1);
  
  printf("int   : [%d, %d]\n", raise(2, sizeof(int)*CHAR_BIT - 1 ) ,
     raise(2, sizeof(int)*CHAR_BIT - 1) - 1);

  printf("long  : [-%lu, %lu]\n\n",
     l_raise(2, sizeof(long)*CHAR_BIT - 1 ) ,
     l_raise(2, sizeof(long)*CHAR_BIT - 1) - 1);

  printf("\t -Unsigned-\n");
  printf("char  : [0, %d]\n", raise(2, sizeof(char)*CHAR_BIT) - 1);
  printf("short : [0, %d]\n", raise(2, sizeof(short)*CHAR_BIT) - 1);
  printf("int   : [0, %u]\n", raise(2, sizeof(int)*CHAR_BIT) - 1);
  printf("long  : [0, %lu]\n", (unsigned long)(raise(2, sizeof(long)*CHAR_BIT))-1);
}

int raise(int base, int n){
  if(n == 0)
    return 1;
  else{
    return base * raise(base, n-1);
  }
}

long l_raise(int base, int n){
  if(n == 0)
    return 1;
  else{
    return base * l_raise(base, n-1);
  }
}
