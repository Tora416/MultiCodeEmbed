#include <stdio.h>


#define MAXLINE 1000
#define SPACES 8     

int getlinee(void);
void entab(void);

char line[MAXLINE];
char lineS[MAXLINE];

main(){
  int len;
  extern char lineS[];

  while(getlinee() > 0 ){
    entab();
    printf("%s", lineS);
  }
}

int getlinee(void){
  int c, i;
  extern char line[];
  
  for(i = 0; i < MAXLINE - 1 && ( c = getchar()) != EOF && c != '\n'; i++)
    line[i] = c;
  if(c == '\n'){
    line[i] = c;
    ++i;
  }  
  line[i] = '\0';
  return i;
}


void entab(void){
  extern char line[];
  extern char lineS[];
  int i, j, cont, aux;
  
  i = j = 0;
  while(line[i] != '\0'){
    if(line[i] == ' '){
      aux = i;
      cont = 0;
      while(line[aux] == ' '){
    ++cont;
    ++aux;
      }
      if(cont % 8 == 0)
    while(cont > 0){
      lineS[j] = '\t';
      ++j;
      cont = cont - 8;
    }
      else{
    if(cont > 8){
      while(cont >= 8){
        lineS[j] = '\t';
        ++j;
        cont = cont - 8;
      }
      for(int l = 0; l < cont; l++){
        lineS[j] = ' ';
        ++j;
      }
    }
    else
      for(int l = 0; l < cont; l++){
        lineS[j] = ' ';
        ++j;
      }
      }
      i = aux;
    }
    else{
      lineS[j] = line[i];
      ++j;
      ++i;
    }
  }
  lineS[j] = '\0';
}
