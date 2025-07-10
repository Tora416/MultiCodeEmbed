


#define TRACE_LEVEL STP_TRACE_LEVEL


#include "stp/stp.h"
#include "stp/stp_conditions.h"
#include "stp/stp_misc.h"
#include "debug.h"


#if (STP_SUPPORT == ENABLED)




bool_t stpRootBridge(StpBridgeContext *context)
{
   bool_t res;

   
   
   if(stpCompareBridgeId(&context->designatedRoot, &context->bridgeId) == 0)
   {
      res = TRUE;
   }
   else
   {
      res = FALSE;
   }

   
   return res;
}




bool_t stpDesignatedBridge(StpBridgeContext *context)
{
   uint_t i;
   bool_t res;
   StpBridgePort *port;

   
   res = FALSE;

   
   for(i = 0; i < context->numPorts; i++)
   {
      
      port = &context->ports[i];

      
      
      if(stpCompareBridgeId(&port->designatedBridge, &context->bridgeId) == 0)
      {
         res = TRUE;
      }
   }

   
   
   return res;
}




bool_t stpRootPort(StpBridgePort *port)
{
   bool_t res;

   
   if(stpComparePortNum(port->portId, port->context->rootPort) == 0)
   {
      res = TRUE;
   }
   else
   {
      res = FALSE;
   }

   
   return res;
}




bool_t stpDesignatedPort(StpBridgePort *port)
{
   bool_t res;
   StpBridgeContext *context;

   
   context = port->context;

   
   
   
   if(stpCompareBridgeId(&port->designatedBridge, &context->bridgeId) == 0 &&
      port->designatedPort == port->portId)
   {
      res = TRUE;
   }
   else
   {
      res = FALSE;
   }

   
   
   return res;
}




bool_t stpSupersedesPortInfo(StpBridgePort *port, const StpBpdu *bpdu)
{
   bool_t res;
   StpBridgeId rootId;
   StpBridgeId bridgeId;
   StpBridgeContext *context;

   
   context = port->context;

   
   
   rootId.priority = ntohs(bpdu->rootId.priority);
   rootId.addr = bpdu->rootId.addr;
   bridgeId.priority = ntohs(bpdu->bridgeId.priority);
   bridgeId.addr = bpdu->bridgeId.addr;

   
   res = FALSE;

   
   
   if(stpCompareBridgeId(&rootId, &port->designatedRoot) < 0)
   {
      
      
      res = TRUE;
   }
   else if(stpCompareBridgeId(&rootId, &port->designatedRoot) > 0)
   {
   }
   else if(ntohl(bpdu->rootPathCost) < port->designatedCost)
   {
      
      
      
      res = TRUE;
   }
   else if(ntohl(bpdu->rootPathCost) > port->designatedCost)
   {
   }
   else if(stpCompareBridgeId(&bridgeId, &port->designatedBridge) < 0)
   {
      
      
      
      res = TRUE;
   }
   else if(stpCompareBridgeId(&bridgeId, &port->designatedBridge) > 0)
   {
   }
   else
   {
      
      
      
      if(stpCompareBridgeId(&bridgeId, &context->bridgeId) != 0)
      {
         
         
         res = TRUE;
      }
      else if(ntohs(bpdu->portId) <= port->designatedPort)
      {
         
         
         res = TRUE;
      }
      else
      {
      }
   }

   
   return res;
}

#endif
