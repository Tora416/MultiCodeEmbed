


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "str.h"




char_t *strDuplicate(const char_t *s)
{
   uint_t n;
   char_t *p;

   
   p = NULL;

   
   if(s != NULL)
   {
      
      n = osStrlen(s) + 1;

      
      p = osAllocMem(n);

      
      if(p != NULL)
      {
         
         osMemcpy(p, s, n);
      }
   }

   
   return p;
}




char_t *strTrimWhitespace(char_t *s)
{
   char_t *end;
   char_t *result;

   
   while(isspace((uint8_t) *s))
   {
      s++;
   }

   
   result = s;

   
   
   for(end = NULL; *s != '\0'; s++)
   {
      if(!isspace((uint8_t) *s))
         end = NULL;
      else if(!end)
         end = s;
   }

   
   if(end)
      *end = '\0';

   
   
   return result;
}




void strRemoveTrailingSpace(char_t *s)
{
   char_t *end;

   
   
   for(end = NULL; *s != '\0'; s++)
   {
      if(!isspace((uint8_t) *s))
         end = NULL;
      else if(!end)
         end = s;
   }

   
   if(end)
      *end = '\0';
}




void strReplaceChar(char_t *s, char_t oldChar, char_t newChar)
{
   
   while(*s != '\0')
   {
      
      if(*s == oldChar)
         *s = newChar;

      
      s++;
   }
}




error_t strSafeCopy(char_t *dest, const char_t *src, size_t destSize)
{
   size_t n;

   
   if(dest == NULL || src == NULL || destSize < 1)
      return ERROR_INVALID_PARAMETER;

   
   n = osStrlen(src);
   
   n = MIN(n, destSize - 1);

   
   osStrncpy(dest, src, n);
   
   dest[n] = '\0';

   
   return NO_ERROR;
}
