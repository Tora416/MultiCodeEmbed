


#define TRACE_LEVEL RSTP_TRACE_LEVEL


#include "rstp/rstp.h"
#include "rstp/rstp_conditions.h"
#include "debug.h"


#if (RSTP_SUPPORT == ENABLED)




uint_t rstpAdminEdge(RstpBridgePort *port)
{
   
   return port->params.adminEdgePort;
}




uint_t rstpAutoEdge(RstpBridgePort *port)
{
   
   return port->params.autoEdgePort;
}




bool_t rstpAllSynced(RstpBridgeContext *context)
{
   uint_t i;
   bool_t res;
   RstpBridgePort *port;

   
   res = TRUE;

   
   
   
   
   for(i = 0; i < context->numPorts; i++)
   {
      
      port = &context->ports[i];

      
      if(!port->selected)
      {
         res = FALSE;
      }
      else if(port->role != port->selectedRole)
      {
         res = FALSE;
      }
      else if(port->updtInfo)
      {
         res = FALSE;
      }
      else if(!port->synced && port->role != STP_PORT_ROLE_ROOT)
      {
         res = FALSE;
      }
      else
      {
         
      }
   }

   
   return res;
}




uint_t rstpEdgeDelay(RstpBridgePort *port)
{
   uint_t value;

   
   
   if(port->operPointToPointMac)
   {
      value = rstpMigrateTime(port->context);
   }
   else
   {
      value = rstpMaxAge(port);
   }

   
   return value;
}




uint_t rstpForwardDelay(RstpBridgePort *port)
{
   uint_t value;

   
   
   if(port->sendRstp)
   {
      value = rstpHelloTime(port);
   }
   else
   {
      value = rstpFwdDelay(port);
   }

   
   return value;
}




uint_t rstpFwdDelay(RstpBridgePort *port)
{
   
   return port->designatedTimes.forwardDelay;
}




uint_t rstpHelloTime(RstpBridgePort *port)
{
   
   return port->designatedTimes.helloTime;
}




uint_t rstpMaxAge(RstpBridgePort *port)
{
   
   return port->designatedTimes.maxAge;
}




uint_t rstpMigrateTime(RstpBridgeContext *context)
{
   
   return context->params.migrateTime;
}




bool_t rstpReRooted(RstpBridgePort *port)
{
   uint_t i;
   bool_t res;
   RstpBridgeContext *context;

   
   res = TRUE;

   
   context = port->context;

   
   for(i = 0; i < context->numPorts; i++)
   {
      
      if(&context->ports[i] != port && context->ports[i].rrWhile != 0)
      {
         res = FALSE;
      }
   }

   
   
   return res;
}




bool_t rstpVersion(RstpBridgeContext *context)
{
   bool_t res;

   
   if(context->params.forceProtocolVersion >= RSTP_PROTOCOL_VERSION)
   {
      
      res = TRUE;
   }
   else
   {
      
      res = FALSE;
   }

   
   return res;
}




bool_t stpVersion(RstpBridgeContext *context)
{
   
   return !rstpVersion(context);
}




uint_t rstpTxHoldCount(RstpBridgeContext *context)
{
   
   return context->params.transmitHoldCount;
}

#endif
