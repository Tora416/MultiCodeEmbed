#include <stdio.h>



#define MAXLINE 1000

int getlinee(char line[]);
void escape(char s[], char t[]);
void inverse_escape(char s[], char t[]);

int main(){
  char s[MAXLINE];
  char t[MAXLINE];
  char r[MAXLINE];
  int len = getlinee(s);

  escape(s, t);
  inverse_escape(t, r);
  printf("word received:%s", s);
  printf("after escape:%s\n", t);
  printf("inverse_escape:%s", r);
}



int getlinee(char line[]){
  int c, i;
  
  for(i = 0; i < MAXLINE - 1 && ( c = getchar()) != EOF && c != '\n'; i++)
    line[i] = c;
  if(c == '\n'){
    line[i] = c;
    ++i;
  }  
  line[i] = '\0';
  return i;
}


void escape(char s[], char t[]){
  int i, j;

  j = 0;
  for(i = 0; s[i] != '\0'; i++)
    switch(s[i]){
    case '\n':
      t[j++] = '\\';
      t[j++] = 'n';
      break;
    case '\t':
      t[j++] = '\\';
      t[j++] = 't';
      break;
    case '\a':
      
      t[j++] = '\\';
      t[j++] = 'a';
      break;
    case '\b':
      t[j++] = '\\';
      t[j++] = 'b';
      break;
    case '\f':
      t[j++] = '\\';
      t[j++] = 'f';
      break;
    case '\r':
      t[j++] = '\\';
      t[j++] = 'r';
      break;
    case '\v':
      t[j++] = '\\';
      t[j++] = 'v';
      break;
    case '\\':
      t[j++] = '\\';
      t[j++] = '\\';
      break;
    case '\?':
      t[j++] = '\\';
      t[j++] = '?';
      break;
    case '\'':
      t[j++] = '\\';
      t[j++] = '\'';
      break;
    case '\"':
      t[j++] = '\\';
      t[j++] ='\"';
      break;
    default:
      t[j++] = s[i];
      break;
    }
  t[j] = '\0';
}


void inverse_escape(char s[], char t[]){
  int i, j;
  
  j = 0;
  for(i = 0; s[i] != '\0'; i++)
    switch(s[i]){
    case '\\':
      switch(s[++i]){
      case 'n':
    t[j++] = '\n';
    break;
      case 't':
    t[j++] = '\t';
    break;
      case 'a':
    t[j++] = '\a';
    break;
      case 'b':
    t[j++] = '\b';
    break;
      case 'f':
    t[j++] = '\f';
    break;
      case 'r':
    t[j++] = '\r';
    break;
      case 'v':
    t[j++] = '\v';
    break;
      case '\\':
    t[j++] = '\\';
    break;
      case '?':
    t[j++] = '\?';
    break;
      case '\'':
    t[j++] = '\'';
    break;
      case '"':
    t[j++] = '\"';
    break;
      }
      break;
    default:
      t[j++] = s[i];
      break;
    }
  t[j] = '\0';
}
