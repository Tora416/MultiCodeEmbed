#include<stdio.h>
#include<string.h>
void prefixSuffixArray(char* pat, int M, int* pps) {
   int length = 0;
   pps[0] = 0;
   int i = 1;
   while (i < M) {
      if (pat[i] == pat[length]) {
         length++;
         pps[i] = length;
         i++;
      } else {
         if (length != 0)
         length = pps[length - 1];
         else {
            pps[i] = 0;
            i++;
         }
      }
   }
}
void KMPAlgorithm(char* text, char* pattern) {
   int M = strlen(pattern),c=0;
   int N = strlen(text);
   int pps[M];
   prefixSuffixArray(pattern, M, pps);
   int i = 0;
   int j = 0;
   while (i < N) {
      if (pattern[j] == text[i]) {
         j++;
         i++;
      }
      if (j == M) {
         c++;
         j = pps[j - 1];
      }
      else if (i < N && pattern[j] != text[i]) {
         if (j != 0)
         j = pps[j - 1];
         else
         i = i + 1;
      }
   }
printf("\n No of matching occurence is:=%d",c);
}
int main() {
   char text[100];
   char pattern[100];
   printf("\n Enter the string ");
   gets(text);
   printf("\n Enter the string ");
   gets(pattern);
  
   KMPAlgorithm(text, pattern);
   return 0;
}
