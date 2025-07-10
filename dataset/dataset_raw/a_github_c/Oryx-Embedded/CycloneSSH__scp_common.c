


#define TRACE_LEVEL SCP_TRACE_LEVEL


#include "ssh/ssh.h"
#include "ssh/ssh_misc.h"
#include "scp/scp_common.h"
#include "debug.h"




size_t scpFormatDirective(const ScpDirective *directive, char_t *buffer)
{
   size_t n;

   
   n = 0;

   
   buffer[n++] = directive->opcode;

   
   if(directive->opcode == SCP_OPCODE_OK)
   {
      
      TRACE_DEBUG("Sending SCP success directive...\r\n");
   }
   else if(directive->opcode == SCP_OPCODE_WARNING ||
      directive->opcode == SCP_OPCODE_ERROR)
   {
      
      n += osSprintf(buffer + n, "%s\n", directive->message);

      
      TRACE_DEBUG("Sending SCP error directive...\r\n");
   }
   else if(directive->opcode == SCP_OPCODE_FILE ||
      directive->opcode == SCP_OPCODE_DIR)
   {
      
      
      n += osSprintf(buffer + n, "%04" PRIo32 " %" PRIu64 " %s\n",
         directive->mode, directive->size, directive->filename);

      
      TRACE_DEBUG("Sending SCP '%c' directive...\r\n", directive->opcode);
   }
   else if(directive->opcode == SCP_OPCODE_END)
   {
      
      buffer[n++] = '\n';

      
      TRACE_DEBUG("Sending SCP '%c' directive...\r\n", directive->opcode);
   }
   else if(directive->opcode == SCP_OPCODE_TIME)
   {
      
      
      n += osSprintf(buffer + n, "%" PRIu32 " 0 %" PRIu32 " 0\n",
         directive->mtime, directive->atime);

      
      TRACE_DEBUG("Sending SCP '%c' directive...\r\n", directive->opcode);
   }
   else
   {
      
   }

   
   return n;
}




error_t scpParseDirective(const char_t *buffer, ScpDirective *directive)
{
   error_t error;
   char_t *p;

   
   error = NO_ERROR;

   
   osMemset(directive, 0, sizeof(ScpDirective));

   
   directive->opcode = (ScpOpcode) buffer[0];

   
   if(directive->opcode == SCP_OPCODE_OK)
   {
      
      TRACE_DEBUG("SCP success directive received...\r\n");
   }
   else if(directive->opcode == SCP_OPCODE_WARNING ||
      directive->opcode == SCP_OPCODE_ERROR)
   {
      
      TRACE_DEBUG("SCP error directive received...\r\n");

      
      directive->message = (char_t *) buffer + 1;
   }
   else if(directive->opcode == SCP_OPCODE_FILE ||
      directive->opcode == SCP_OPCODE_DIR)
   {
      
      TRACE_DEBUG("SCP '%c' directive received...\r\n", directive->opcode);

      
      do
      {
         
         directive->mode = osStrtoul(buffer + 1, &p, 8);

         
         if(!osIsblank(*p))
         {
            error = ERROR_INVALID_SYNTAX;
            break;
         }

         
         while(osIsblank(*p))
         {
            p++;
         }

         
         directive->size = osStrtoull(p, &p, 10);

         
         if(!osIsblank(*p))
         {
            error = ERROR_INVALID_SYNTAX;
            break;
         }

         
         while(osIsblank(*p))
         {
            p++;
         }

         
         directive->filename = p;

         
      } while(0);
   }
   else if(directive->opcode == SCP_OPCODE_END)
   {
      
      TRACE_DEBUG("SCP '%c' directive received...\r\n", directive->opcode);
   }
   else if(directive->opcode == SCP_OPCODE_TIME)
   {
      
      TRACE_DEBUG("SCP '%c' directive received...\r\n", directive->opcode);

      
      do
      {
         
         directive->mtime = osStrtoul(buffer + 1, &p, 10);

         
         if(!osIsblank(*p))
         {
            error = ERROR_INVALID_SYNTAX;
            break;
         }

         
         osStrtoul(p, &p, 10);

         
         if(!osIsblank(*p))
         {
            error = ERROR_INVALID_SYNTAX;
            break;
         }

         
         directive->atime = osStrtoul(p, &p, 10);

         
         if(!osIsblank(*p))
         {
            error = ERROR_INVALID_SYNTAX;
            break;
         }

         
         osStrtoul(p, &p, 10);

         
         if(*p != '\0')
         {
            error = ERROR_INVALID_SYNTAX;
            break;
         }

         
      } while(0);
   }
   else
   {
      
      TRACE_WARNING("SCP unknown directive received...\r\n");

      
      error = ERROR_INVALID_COMMAND;
   }

   
   return error;
}
