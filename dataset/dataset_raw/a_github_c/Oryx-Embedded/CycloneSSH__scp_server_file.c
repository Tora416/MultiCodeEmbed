


#define TRACE_LEVEL SCP_TRACE_LEVEL


#include "ssh/ssh.h"
#include "scp/scp_server.h"
#include "scp/scp_server_file.h"
#include "scp/scp_server_misc.h"
#include "path.h"
#include "debug.h"


#if (SCP_SERVER_SUPPORT == ENABLED)




error_t scpServerOpenFileForWriting(ScpServerSession *session,
   const char_t *filename, uint32_t mode, uint64_t size)
{
   error_t error;
   uint_t perm;
   ScpServerContext *context;

   
   context = session->context;

   
   if(fsDirExists(session->path) || session->recursive)
   {
      
      pathCopy(context->path, session->path, SCP_SERVER_MAX_PATH_LEN);
      pathCombine(context->path, filename, SCP_SERVER_MAX_PATH_LEN);
      pathCanonicalize(context->path);
   }
   else
   {
      
      pathCopy(context->path, session->path, SCP_SERVER_MAX_PATH_LEN);
   }

   
   perm = scpServerGetFilePermissions(session, context->path);

   
   if((perm & SCP_FILE_PERM_WRITE) != 0)
   {
      
      session->file = fsOpenFile(context->path, FS_FILE_MODE_WRITE |
         FS_FILE_MODE_CREATE | FS_FILE_MODE_TRUNC);

      
      if(session->file != NULL)
      {
         
         session->fileSize = size;
         session->fileOffset = 0;

         
         error = NO_ERROR;
      }
      else
      {
         
         error = ERROR_FILE_NOT_FOUND;
      }
   }
   else
   {
      
      error = ERROR_ACCESS_DENIED;
   }

   
   return error;
}




error_t scpServerOpenFileForReading(ScpServerSession *session)
{
   error_t error;
   uint_t perm;
   FsFileStat fileStat;

   
   error = fsGetFileStat(session->path, &fileStat);

   
   if(!error)
   {
      
      if((fileStat.attributes & FS_FILE_ATTR_DIRECTORY) == 0)
      {
         
         perm = scpServerGetFilePermissions(session, session->path);

         
         if((perm & SCP_FILE_PERM_READ) != 0)
         {
            
            session->file = fsOpenFile(session->path, FS_FILE_MODE_READ);

            
            if(session->file != NULL)
            {
               
               session->fileSize = fileStat.size;
               session->fileOffset = 0;

               
               
               if((fileStat.attributes & FS_FILE_ATTR_READ_ONLY) != 0)
               {
                  session->fileMode = SCP_MODE_IRUSR | SCP_MODE_IRGRP |
                     SCP_MODE_IROTH;
               }
               else
               {
                  session->fileMode = SCP_MODE_IRUSR | SCP_MODE_IWUSR |
                     SCP_MODE_IRGRP | SCP_MODE_IWGRP | SCP_MODE_IROTH |
                     SCP_MODE_IWOTH;
               }

               
               error = NO_ERROR;
            }
            else
            {
               
               error = ERROR_FILE_NOT_FOUND;
            }
         }
         else
         {
            
            error = ERROR_ACCESS_DENIED;
         }
      }
      else
      {
         
         error = ERROR_FILE_NOT_FOUND;
      }
   }
   else
   {
      
      error = ERROR_FILE_NOT_FOUND;
   }

   
   return error;
}




error_t scpServerWriteData(ScpServerSession *session)
{
   error_t error;
   size_t n;

   
   error = NO_ERROR;

   
   if(session->bufferPos < session->bufferLen)
   {
      
      error = sshReadChannel(session->channel,
         session->buffer + session->bufferPos,
         session->bufferLen - session->bufferPos, &n, 0);

      
      if(!error)
      {
         
         session->bufferPos += n;
      }
   }
   else if(session->fileOffset < session->fileSize)
   {
      
      if(session->bufferLen > 0)
      {
         
         if(session->statusCode == NO_ERROR)
         {
            
            session->statusCode = fsWriteFile(session->file, session->buffer,
               session->bufferLen);
         }

         
         session->fileOffset += session->bufferLen;
      }

      
      if((session->fileSize - session->fileOffset) < SCP_SERVER_BUFFER_SIZE)
      {
         n = (size_t) (session->fileSize - session->fileOffset);
      }
      else
      {
         n = SCP_SERVER_BUFFER_SIZE;
      }

      
      session->bufferLen = n;
      session->bufferPos = 0;
   }
   else
   {
      
      fsCloseFile(session->file);
      session->file = NULL;

      
      session->bufferLen = 0;
      session->bufferPos = 0;

      
      if(session->statusCode == NO_ERROR)
      {
         session->state = SCP_SERVER_SESSION_STATE_WRITE_STATUS;
      }
      else
      {
         session->state = SCP_SERVER_SESSION_STATE_ERROR;
      }
   }

   
   return error;
}




error_t scpServerReadData(ScpServerSession *session)
{
   error_t error;
   size_t n;
   size_t length;

   
   error = NO_ERROR;

   
   if(session->bufferPos < session->bufferLen)
   {
      
      error = sshWriteChannel(session->channel,
         session->buffer + session->bufferPos,
         session->bufferLen - session->bufferPos, &n, 0);

      
      if(error == NO_ERROR || error == ERROR_TIMEOUT)
      {
         
         session->bufferPos += n;
      }
   }
   else if(session->fileOffset < session->fileSize)
   {
      
      if((session->fileSize - session->fileOffset) < SCP_SERVER_BUFFER_SIZE)
      {
         length = (size_t) (session->fileSize - session->fileOffset);
      }
      else
      {
         length = SCP_SERVER_BUFFER_SIZE;
      }

      
      error = fsReadFile(session->file, session->buffer, length, &n);

      
      if(!error)
      {
         
         if(n == length)
         {
            
            session->fileOffset += n;

            
            session->bufferLen = n;
            session->bufferPos = 0;
         }
         else
         {
            
            error = ERROR_READ_FAILED;
         }
      }
   }
   else
   {
      
      fsCloseFile(session->file);
      session->file = NULL;

      
      if(session->recursive)
      {
         
         pathRemoveFilename(session->path);
         pathRemoveSlash(session->path);
      }

      
      session->bufferLen = 0;
      session->bufferPos = 0;

      
      session->state = SCP_SERVER_SESSION_STATE_READ_STATUS;
   }

   
   return error;
}

#endif
