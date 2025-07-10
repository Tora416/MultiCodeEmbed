


#define TRACE_LEVEL SFTP_TRACE_LEVEL


#include "ssh/ssh.h"
#include "sftp/sftp_server.h"
#include "sftp/sftp_server_directory.h"
#include "sftp/sftp_server_misc.h"
#include "path.h"
#include "debug.h"


#if (SFTP_SERVER_SUPPORT == ENABLED)




error_t sftpServerCreateDir(SftpServerSession *session,
   const SshString *path, const SftpFileAttrs *attributes)
{
   error_t error;
   uint_t perm;
   SftpServerContext *context;

   
   context = session->context;

   
   error = sftpServerGetPath(session, path, context->path,
      SFTP_SERVER_MAX_PATH_LEN);
   
   if(error)
      return error;

   
   perm = sftpServerGetFilePermissions(session, context->path);
   
   if((perm & SFTP_FILE_PERM_WRITE) == 0)
      return ERROR_ACCESS_DENIED;

   
   error = fsCreateDir(context->path);

   
   return error;
}




error_t sftpServerRemoveDir(SftpServerSession *session,
   const SshString *path)
{
   error_t error;
   uint_t perm;
   SftpServerContext *context;

   
   context = session->context;

   
   error = sftpServerGetPath(session, path, context->path,
      SFTP_SERVER_MAX_PATH_LEN);
   
   if(error)
      return error;

   
   perm = sftpServerGetFilePermissions(session, context->path);
   
   if((perm & SFTP_FILE_PERM_WRITE) == 0)
      return ERROR_ACCESS_DENIED;

   
   error = fsRemoveDir(context->path);

   
   return error;
}




error_t sftpServerOpenDir(SftpServerSession *session,
   const SshString *path, uint32_t *handle)
{
   error_t error;
   uint_t i;
   uint_t perm;
   SftpServerContext *context;
   SftpFileObject *fileObject;

   
   context = session->context;

   
   error = sftpServerGetPath(session, path, context->path,
      SFTP_SERVER_MAX_PATH_LEN);
   
   if(error)
      return error;

   
   perm = sftpServerGetFilePermissions(session, context->path);
   
   if((perm & SFTP_FILE_PERM_READ) == 0)
      return ERROR_ACCESS_DENIED;

   
   for(i = 0; i < context->numFileObjects; i++)
   {
      
      fileObject = &context->fileObjects[i];

      
      if(fileObject->type == SSH_FILEXFER_TYPE_INVALID)
      {
         break;
      }
   }

   
   if(i < context->numFileObjects)
   {
      
      fileObject->dir = fsOpenDir(context->path);

      
      if(fileObject->dir != NULL)
      {
         
         fileObject->type = SSH_FILEXFER_TYPE_DIRECTORY;
         fileObject->session = session;
         fileObject->size = 0;
         fileObject->offset = 0;
         fileObject->file = NULL;

         
         osStrcpy(fileObject->path, context->path);

         
         fileObject->handle = sftpServerGenerateHandle(session);

         
         
         *handle = fileObject->handle;

         
         error = NO_ERROR;
      }
      else
      {
         
         error = ERROR_OPEN_FAILED;
      }
   }
   else
   {
      
      error = ERROR_OUT_OF_RESOURCES;
   }

   
   return error;
}




error_t sftpServerReadDir(SftpServerSession *session,
   const SshBinaryString *handle, SftpName *name)
{
   error_t error;
   uint_t perm;
   FsDirEntry dirEntry;
   SftpServerContext *context;
   SftpFileObject *fileObject;

   
   error = NO_ERROR;

   
   context = session->context;

   
   osMemset(name, 0, sizeof(SftpName));

   
   
   fileObject = sftpServerFindDir(session, handle);
   
   if(fileObject == NULL)
      return ERROR_INVALID_HANDLE;

   
   while(!error)
   {
      
      error = fsReadDir(fileObject->dir, &dirEntry);

      
      if(!error)
      {
         
         pathCopy(context->path, fileObject->path, SFTP_SERVER_MAX_PATH_LEN);
         pathCombine(context->path, dirEntry.name, SFTP_SERVER_MAX_PATH_LEN);
         pathCanonicalize(context->path);

         
         perm = sftpServerGetFilePermissions(session, context->path);

         
         if((perm & SFTP_FILE_PERM_READ) != 0)
         {
            
            osStrcpy(context->path, dirEntry.name);

            
            name->filename.value = context->path;
            name->filename.length = osStrlen(context->path);

            
            if((dirEntry.attributes & FS_FILE_ATTR_DIRECTORY) != 0)
            {
               name->attributes.type = SSH_FILEXFER_TYPE_DIRECTORY;
            }
            else
            {
               name->attributes.type = SSH_FILEXFER_TYPE_REGULAR;
            }

            
            name->attributes.size = dirEntry.size;

            
            if((dirEntry.attributes & FS_FILE_ATTR_READ_ONLY) != 0)
            {
               name->attributes.permissions = SFTP_MODE_IRUSR;
            }
            else
            {
               name->attributes.permissions = SFTP_MODE_IRUSR | SFTP_MODE_IWUSR;
            }

            
            name->attributes.mtime = dirEntry.modified;
            name->attributes.atime = dirEntry.modified;

            
            if((dirEntry.attributes & FS_FILE_ATTR_READ_ONLY) != 0)
            {
               name->attributes.bits |= SSH_FILEXFER_ATTR_FLAGS_READONLY;
            }

            if((dirEntry.attributes & FS_FILE_ATTR_SYSTEM) != 0)
            {
               name->attributes.bits |= SSH_FILEXFER_ATTR_FLAGS_SYSTEM;
            }

            if((dirEntry.attributes & FS_FILE_ATTR_HIDDEN) != 0)
            {
               name->attributes.bits |= SSH_FILEXFER_ATTR_FLAGS_HIDDEN;
            }

            if((dirEntry.attributes & FS_FILE_ATTR_ARCHIVE) != 0)
            {
               name->attributes.bits |= SSH_FILEXFER_ATTR_FLAGS_ARCHIVE;
            }

            
            name->attributes.flags = SSH_FILEXFER_ATTR_SIZE |
               SSH_FILEXFER_ATTR_PERMISSIONS | SSH_FILEXFER_ATTR_ACMODTIME;

            
            break;
         }
      }
   }

   
   return error;
}




error_t sftpServerCloseDir(SftpServerSession *session,
   const SshBinaryString *handle)
{
   error_t error;
   SftpFileObject *fileObject;

   
   
   fileObject = sftpServerFindDir(session, handle);

   
   if(fileObject != NULL)
   {
      
      fsCloseDir(fileObject->dir);
      fileObject->dir = NULL;

      
      fileObject->type = SSH_FILEXFER_TYPE_INVALID;

      
      error = NO_ERROR;
   }
   else
   {
      
      error = ERROR_INVALID_HANDLE;
   }

   
   return error;
}




SftpFileObject *sftpServerFindDir(SftpServerSession *session,
   const SshBinaryString *handle)
{
   uint_t i;
   SftpServerContext *context;
   SftpFileObject *fileObject;

   
   context = session->context;

   
   if(handle->length == sizeof(uint32_t))
   {
      
      for(i = 0; i < context->numFileObjects; i++)
      {
         
         fileObject = &context->fileObjects[i];

         
         if(fileObject->type == SSH_FILEXFER_TYPE_DIRECTORY &&
            fileObject->session == session &&
            fileObject->handle == LOAD32BE(handle->value))
         {
            
            return fileObject;
         }
      }
   }

   
   return NULL;
}

#endif
