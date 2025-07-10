


#include "debug.h"




void debugDisplayArray(FILE *stream,
   const char_t *prepend, const void *data, size_t length)
{
   uint_t i;

   
   for(i = 0; i < length; i++)
   {
      
      if((i % 16) == 0)
      {
         TRACE_PRINTF("%s", prepend);
      }

      
      TRACE_PRINTF("%02" PRIX8 " ", *((const uint8_t *) data + i));

      
      if((i % 16) == 15 || i == (length - 1))
      {
         TRACE_PRINTF("\r\n");
      }
   }
}
