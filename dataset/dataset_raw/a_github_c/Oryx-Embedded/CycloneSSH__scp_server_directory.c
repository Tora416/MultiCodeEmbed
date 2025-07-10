


#define TRACE_LEVEL SCP_TRACE_LEVEL


#include "ssh/ssh.h"
#include "scp/scp_server.h"
#include "scp/scp_server_file.h"
#include "scp/scp_server_directory.h"
#include "scp/scp_server_misc.h"
#include "path.h"
#include "debug.h"


#if (SCP_SERVER_SUPPORT == ENABLED)




error_t scpServerCreateDir(ScpServerSession *session, const char_t *name)
{
   error_t error;
   uint_t perm;

   
   pathCombine(session->path, name, SCP_SERVER_MAX_PATH_LEN);
   pathCanonicalize(session->path);
   pathRemoveSlash(session->path);

   
   if(!fsDirExists(session->path))
   {
      
      perm = scpServerGetFilePermissions(session, session->path);

      
      if((perm & SCP_FILE_PERM_WRITE) != 0)
      {
         
         error = fsCreateDir(session->path);

         
         if(error)
         {
            
            error = ERROR_DIRECTORY_NOT_FOUND;
         }
      }
      else
      {
         
         error = ERROR_ACCESS_DENIED;
      }
   }
   else
   {
      
      error = NO_ERROR;
   }

   
   if(!error)
   {
      
      session->dirLevel++;
   }

   
   return error;
}




error_t scpServerOpenDir(ScpServerSession *session)
{
   error_t error;
   uint_t perm;

   
   perm = scpServerGetFilePermissions(session, session->path);

   
   if((perm & SCP_FILE_PERM_READ) != 0)
   {
      
      session->dir[session->dirLevel] = fsOpenDir(session->path);

      
      if(session->dir[session->dirLevel] != NULL)
      {
         
         
         session->fileMode = SCP_MODE_IRWXU | SCP_MODE_IRWXG | SCP_MODE_IRWXO;

         
         error = NO_ERROR;
      }
      else
      {
         
         error = ERROR_DIRECTORY_NOT_FOUND;
      }
   }
   else
   {
      
      error = ERROR_ACCESS_DENIED;
   }

   
   return error;
}




void scpServerGetNextDirEntry(ScpServerSession *session)
{
   error_t error;
   uint_t perm;
   FsDirEntry dirEntry;

   
   while(1)
   {
      
      error = fsReadDir(session->dir[session->dirLevel], &dirEntry);

      
      if(!error)
      {
         
         if(!osStrcmp(dirEntry.name, ".") || !osStrcmp(dirEntry.name, ".."))
         {
            
         }
         else
         {
            
            pathCombine(session->path, dirEntry.name, SCP_SERVER_MAX_PATH_LEN);
            pathCanonicalize(session->path);

            
            perm = scpServerGetFilePermissions(session, session->path);

            
            if((perm & SCP_FILE_PERM_LIST) != 0)
            {
               
               if((dirEntry.attributes & FS_FILE_ATTR_DIRECTORY) != 0)
               {
                  
                  if((session->dirLevel + 1) < SCP_SERVER_MAX_RECURSION_LEVEL)
                  {
                     
                     session->dirLevel++;

                     
                     error = scpServerOpenDir(session);

                     
                     if(error)
                     {
                        
                        session->dirLevel--;
                     }
                  }
                  else
                  {
                     
                     error = ERROR_OPEN_FAILED;
                  }
               }
               else
               {
                  
                  error = scpServerOpenFileForReading(session);
               }

               
               if(!error)
               {
                  break;
               }
            }

            
            pathRemoveFilename(session->path);
            pathRemoveSlash(session->path);
         }
      }
      else
      {
         
         break;
      }
   }

   
   if(error)
   {
      
      fsCloseDir(session->dir[session->dirLevel]);
      session->dir[session->dirLevel] = NULL;

      
      if(session->dirLevel > 0)
      {
         pathRemoveFilename(session->path);
         pathRemoveSlash(session->path);
      }
   }

   
   session->state = SCP_SERVER_SESSION_STATE_READ_COMMAND;
}

#endif
