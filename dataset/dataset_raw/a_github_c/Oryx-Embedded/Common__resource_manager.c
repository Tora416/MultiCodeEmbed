


#include <string.h>
#include "os_port.h"
#include "resource_manager.h"
#include "debug.h"


extern const uint8_t res[];


error_t resGetData(const char_t *path, const uint8_t **data, size_t *length)
{
   bool_t found;
   bool_t match;
   uint_t n;
   uint_t dirLength;
   ResEntry *resEntry;

   
   ResHeader *resHeader = (ResHeader *) res;

   
   if(resHeader->totalSize < sizeof(ResHeader))
      return ERROR_INVALID_RESOURCE;

   
   dirLength = resHeader->rootEntry.dataLength;
   
   resEntry = (ResEntry *) (res + resHeader->rootEntry.dataStart);

   
   for(found = FALSE; !found && path[0] != '\0'; path += n + 1)
   {
      
      for(n = 0; path[n] != '\\' && path[n] != '/' && path[n] != '\0'; n++);

      if(n == 0 && path[n] != '\0')
      {
         path++;
         for(n = 0; path[n] != '\\' && path[n] != '/' && path[n] != '\0'; n++);
      }

      
      for(match = FALSE; !match && dirLength > 0; )
      {
         
         if(dirLength < sizeof(ResEntry))
            return ERROR_INVALID_RESOURCE;
         
         if(dirLength < (sizeof(ResEntry) + resEntry->nameLength))
            return ERROR_INVALID_RESOURCE;

         
         if(resEntry->nameLength == n && !strncasecmp(resEntry->name, path, n))
         {
            
            if(resEntry->type == RES_TYPE_DIR)
            {
               
               dirLength = resEntry->dataLength;
               
               resEntry = (ResEntry *) (res + resEntry->dataStart);
            }
            else
            {
               
               if(path[n] != '\0')
                  return ERROR_NOT_FOUND;

               
               found = TRUE;
            }
            
            match = TRUE;
         }
         else
         {
            
            dirLength -= sizeof(ResEntry) + resEntry->nameLength;
            
            resEntry = (ResEntry *) ((uint8_t *) resEntry + sizeof(ResEntry) + resEntry->nameLength);
         }
      }

      
      if(!match)
         return ERROR_NOT_FOUND;
   }

   
   if(!found)
      return ERROR_NOT_FOUND;
   
   if(resEntry->type != RES_TYPE_FILE)
      return ERROR_NOT_FOUND;

   
   *data = res + resEntry->dataStart;
   
   *length = resEntry->dataLength;

   
   return NO_ERROR;
}


error_t resSearchFile(const char_t *path, DirEntry *dirEntry)
{
   bool_t found;
   bool_t match;
   uint_t n;
   uint_t length;
   ResEntry *resEntry;

   
   ResHeader *resHeader = (ResHeader *) res;

   
   if(resHeader->totalSize < sizeof(ResHeader))
      return ERROR_INVALID_RESOURCE;

   
   length = resHeader->rootEntry.dataLength;
   
   resEntry = (ResEntry *) (res + resHeader->rootEntry.dataStart);

   
   for(found = FALSE; !found && path[0] != '\0'; path += n + 1)
   {
      
      for(n = 0; path[n] != '\\' && path[n] != '/' && path[n] != '\0'; n++);

      if(n == 0 && path[n] != '\0')
      {
         path++;
         for(n = 0; path[n] != '\\' && path[n] != '/' && path[n] != '\0'; n++);
      }

      
      for(match = FALSE; !match && length > 0; )
      {
         
         if(length < sizeof(ResEntry))
            return ERROR_INVALID_RESOURCE;
         
         if(length < (sizeof(ResEntry) + resEntry->nameLength))
            return ERROR_INVALID_RESOURCE;

         
         if(resEntry->nameLength == n && !strncasecmp(resEntry->name, path, n))
         {
            
            if(resEntry->type == RES_TYPE_DIR)
            {
               
               length = resEntry->dataLength;
               
               resEntry = (ResEntry *) (res + resEntry->dataStart);
            }
            else
            {
               
               if(path[n] != '\0')
                  return ERROR_INVALID_PATH;

               
               found = TRUE;
            }
            
            match = TRUE;
         }
         else
         {
            
            length -= sizeof(ResEntry) + resEntry->nameLength;
            
            resEntry = (ResEntry *) ((uint8_t *) resEntry + sizeof(ResEntry) + resEntry->nameLength);
         }
      }

      
      if(!match)
         return ERROR_NOT_FOUND;
   }

   
   if(!found)
      return ERROR_NOT_FOUND;

   
   dirEntry->type = resEntry->type;
   dirEntry->volume = 0;
   dirEntry->dataStart = resEntry->dataStart;
   dirEntry->dataLength = resEntry->dataLength;
   dirEntry->nameLength = 0; 
   
   
   
   

   
   return NO_ERROR;
}

#if 0

error_t resOpenFile(FsFile *file, const DirEntry *dirEntry, uint_t mode)
{
   file->mode = mode;
   file->offset = 0;
   file->start = dirEntry->dataStart;
   file->size = dirEntry->dataLength;

   return NO_ERROR;
}


error_t resSeekFile(FsFile *file, uint32_t *position)
{
   return ERROR_NOT_IMPLEMENTED;
}


uint_t resReadFile(FsFile *file, void *data, size_t length)
{
   length = MIN(length, file->size - file->offset);
   osMemcpy(data, res + file->start + file->offset, length);
   file->offset += length;
   return length;
}

FILE *fopen(const char_t *filename, const char_t *mode)
{
   error_t error;
   DirEntry dirEntry;
   FsFile *file;

   error = resSearchFile(filename, &dirEntry);
   if(error)
      return NULL;

   file = osAllocMem(sizeof(FsFile));
   if(!file)
      return NULL;

   error = resOpenFile(file, &dirEntry, MODE_BINARY);
   if(error)
   {
      osFreeMem(file);
      return NULL;
   }

   return (FILE *) file;
}


size_t fread(void *ptr, size_t size, size_t count, FILE *stream)
{
   uint_t n;

   n = resReadFile((FsFile *) stream, ptr, size * count);

   return n / size;
}


int_t fclose(FILE * stream)
{
   osFreeMem(stream);
   
   return 0;
}


uint_t fileGetSize(FILE *stream)
{
   uint_t n;
   n = ((FsFile *) stream)->size;
   return n;
}

#endif
