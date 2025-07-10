


#include <string.h>
#include <ctype.h>
#include "path.h"




bool_t pathIsAbsolute(const char_t *path)
{
   
   if(path[0] == '/' || path[0] == '\\')
      return TRUE;
   else
      return FALSE;
}




bool_t pathIsRelative(const char_t *path)
{
   
   if(path[0] == '/' || path[0] == '\\')
      return FALSE;
   else
      return TRUE;
}




const char_t *pathGetFilename(const char_t *path)
{
   size_t n;

   
   n = osStrlen(path);

   
   while(n > 0)
   {
      
      if(path[n - 1] != '/' && path[n - 1] != '\\')
         break;

      
      n--;
   }

   
   while(n > 0)
   {
      
      if(path[n - 1] == '/' || path[n - 1] == '\\')
         break;

      
      n--;
   }

   
   return path + n;
}




void pathRemoveFilename(char_t *path)
{
   char_t *p;

   
   p = (char_t *) pathGetFilename(path);
   *p = '\0';
}




void pathCopy(char_t *dest, const char_t *src, size_t maxLen)
{
   size_t n;

   
   n = osStrlen(src);
   
   n = MIN(n, maxLen);

   
   osStrncpy(dest, src, n);
   
   dest[n] = '\0';
}




void pathCanonicalize(char_t *path)
{
   size_t i;
   size_t j;
   size_t k;

   
   i = 0;
   k = 0;

   
   while(path[i] != '\0')
   {
      
      if(path[i] == '/' || path[i] == '\\')
      {
         path[k++] = '/';
         while(path[i] == '/' || path[i] == '\\') i++;
      }
      else
      {
         path[k++] = path[i++];
      }
   }

   
   path[k] = '\0';

   
   i = 0;
   j = 0;
   k = 0;

   
   do
   {
      
      if(path[i] == '/' || path[i] == '\0')
      {
         
         if((i - j) == 1 && !osStrncmp(path + j, ".", 1))
         {
            
            if(k == 0)
            {
               if(path[i] == '\0')
               {
                  path[k++] = '.';
               }
               else if(path[i] == '/' && path[i + 1] == '\0')
               {
                  path[k++] = '.';
                  path[k++] = '/';
               }
            }
            else if(k > 1)
            {
               
               if(path[i] == '\0')
                  k--;
            }
         }
         
         else if((i - j) == 2 && !osStrncmp(path + j, "..", 2))
         {
            
            if(k == 0)
            {
               path[k++] = '.';
               path[k++] = '.';

               
               if(path[i] == '/')
                  path[k++] = '/';
            }
            else if(k > 1)
            {
               
               for(j = 1; j < k; j++)
               {
                  if(path[k - j - 1] == '/')
                     break;
               }

               
               if(j < k)
               {
                  if(!osStrncmp(path + k - j, "..", 2))
                  {
                     path[k++] = '.';
                     path[k++] = '.';
                  }
                  else
                  {
                     k = k - j - 1;
                  }

                  
                  if(k == 0 && path[0] == '/')
                     path[k++] = '/';
                  else if(path[i] == '/')
                     path[k++] = '/';
               }
               
               else
               {
                  if(k == 3 && !osStrncmp(path, "..", 2))
                  {
                     path[k++] = '.';
                     path[k++] = '.';

                     
                     if(path[i] == '/')
                        path[k++] = '/';
                  }
                  else if(path[i] == '\0')
                  {
                     k = 0;
                     path[k++] = '.';
                  }
                  else if(path[i] == '/' && path[i + 1] == '\0')
                  {
                     k = 0;
                     path[k++] = '.';
                     path[k++] = '/';
                  }
                  else
                  {
                     k = 0;
                  }
               }
            }
         }
         else
         {
            
            osMemmove(path + k, path + j, i - j);
            
            k += i - j;

            
            if(path[i] == '/')
               path[k++] = '/';
         }

         
         while(path[i] == '/') i++;
         j = i;
      }
   } while(path[i++] != '\0');

   
   path[k] = '\0';
}




void pathAddSlash(char_t *path, size_t maxLen)
{
   size_t n;

   
   n = osStrlen(path);

   
   if(!n)
   {
      
      if(maxLen >= 1)
         osStrcpy(path, "/");
   }
   else if(path[n - 1] != '/' && path[n - 1] != '\\')
   {
      
      if(maxLen >= (n + 1))
         osStrcat(path, "/");
   }
}




void pathRemoveSlash(char_t *path)
{
   char_t *end;

   
   if(pathIsAbsolute(path))
      path++;

   
   for(end = NULL; *path != '\0'; path++)
   {
      if(*path != '/' && *path != '\\')
         end = NULL;
      else if(!end)
         end = path;
   }

   
   if(end)
      *end = '\0';
}




void pathCombine(char_t *path, const char_t *more, size_t maxLen)
{
   size_t n1;
   size_t n2;

   
   if(*path != '\0')
      pathAddSlash(path, maxLen);

   
   while(*more == '/' || *more == '\\') more++;

   
   n1 = osStrlen(path);
   
   n2 = osStrlen(more);

   
   if(n1 < maxLen)
   {
      
      n2 = MIN(n2, maxLen - n1);
      
      osStrncpy(path + n1, more, n2);
      
      path[n1 + n2] = '\0';
   }
}




bool_t pathMatch(const char_t *path, const char_t *pattern)
{
   size_t i = 0;
   size_t j = 0;

   
   while(pattern[j] != '\0')
   {
      
      if(pattern[j] == '?')
      {
         
         if(path[i] == '\0')
         {
            return FALSE;
         }
         else
         {
            
            i++;
            
            j++;
         }
      }
      else if(pattern[j] == '*')
      {
         
         if(path[i] == '\0')
         {
            
            j++;
         }
         else if(pathMatch(path + i, pattern + j + 1))
         {
            return TRUE;
         }
         else
         {
            
            i++;
         }
      }
      else
      {
         
         if(osTolower(path[i]) != osTolower(pattern[j]))
         {
            return FALSE;
         }
         else
         {
            
            i++;
            
            j++;
         }
      }
   }

   
   if(path[i] == '\0' && pattern[j] == '\0')
      return TRUE;
   else
      return FALSE;
}
