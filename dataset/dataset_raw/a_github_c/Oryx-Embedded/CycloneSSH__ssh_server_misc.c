


#define TRACE_LEVEL SSH_TRACE_LEVEL


#include "ssh/ssh.h"
#include "ssh/ssh_server.h"
#include "ssh/ssh_server_misc.h"
#include "ssh/ssh_transport.h"
#include "ssh/ssh_channel.h"
#include "ssh/ssh_misc.h"
#include "debug.h"


#if (SSH_SUPPORT == ENABLED && SSH_SERVER_SUPPORT == ENABLED)




void sshServerTick(SshServerContext *context)
{
   error_t error;
   uint_t i;
   systime_t time;
   SshConnection *connection;

   
   time = osGetSystemTime();

   
   for(i = 0; i < context->sshContext.numConnections; i++)
   {
      
      connection = &context->sshContext.connections[i];

      
      if(connection->state != SSH_CONN_STATE_CLOSED)
      {
         
         if(timeCompare(time, connection->timestamp + SSH_SERVER_TIMEOUT) >= 0)
         {
            
            TRACE_INFO("SSH server: Closing inactive connection...\r\n");

            
            error = sshSendDisconnect(connection, SSH_DISCONNECT_BY_APPLICATION,
               "Session idle timeout");

            
            if(error)
            {
               
               sshCloseConnection(connection);
            }
         }
      }
   }
}




void sshServerAcceptConnection(SshServerContext *context)
{
   Socket *socket;
   IpAddr clientIpAddr;
   uint16_t clientPort;
   SshConnection *connection;

   
   socket = socketAccept(context->socket, &clientIpAddr, &clientPort);

   
   if(socket != NULL)
   {
      
      connection = sshOpenConnection(&context->sshContext, socket);

      
      
      if(connection != NULL)
      {
         
         TRACE_INFO("SSH server: Connection established with client %s port %"
            PRIu16 "...\r\n", ipAddrToString(&clientIpAddr, NULL), clientPort);

         
         socketSetTimeout(socket, 0);
      }
      else
      {
         
         TRACE_INFO("SSH Server: Connection refused with client %s port %"
            PRIu16 "...\r\n", ipAddrToString(&clientIpAddr, NULL), clientPort);

         
         socketClose(socket);
      }
   }
}

#endif
