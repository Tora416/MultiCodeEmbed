


#define TRACE_LEVEL RSTP_TRACE_LEVEL


#include "rstp/rstp.h"
#include "rstp/rstp_fsm.h"
#include "rstp/rstp_misc.h"
#include "debug.h"


#if (RSTP_SUPPORT == ENABLED)




void rstpFsmInit(RstpBridgeContext *context)
{
   uint_t i;
   RstpBridgePort *port;

   
   
   
   context->bridgePriority.rootBridgeId = context->bridgeId;
   context->bridgePriority.rootPathCost = 0;
   context->bridgePriority.designatedBridgeId = context->bridgeId;
   context->bridgePriority.designatedPortId = 0;
   context->bridgePriority.bridgePortId = 0;

   
   
   context->bridgeTimes.forwardDelay = context->params.bridgeForwardDelay;
   context->bridgeTimes.helloTime = context->params.bridgeHelloTime;
   context->bridgeTimes.maxAge = context->params.bridgeMaxAge;
   context->bridgeTimes.messageAge = 0;

   
   context->rootPriority = context->bridgePriority;
   
   context->rootTimes = context->bridgeTimes;

   
   context->ageingTime = context->params.ageingTime;
   
   context->rapidAgeingWhile = 0;

   
   rstpUpdateAgeingTime(context, context->params.ageingTime);

   
   osMemset(&context->bpdu, 0, sizeof(RstpBpdu));

   
   for(i = 0; i < context->numPorts; i++)
   {
      
      port = &context->ports[i];

      
      
      
      port->designatedTimes = context->rootTimes;
      port->designatedTimes.helloTime = context->bridgeTimes.helloTime;

      
      memset(&port->msgPriority, 0, sizeof(RstpPriority));
      memset(&port->msgTimes, 0, sizeof(RstpTimes));

      
      port->disputed = FALSE;
      port->rcvdInfo = RSTP_RCVD_INFO_OTHER;
      port->rcvdTc = FALSE;
      port->rcvdTcAck = FALSE;
      port->rcvdTcn = FALSE;
      port->tcProp = FALSE;
      port->updtInfo = FALSE;
   }

   
   
   rstpPrsInit(context);

   
   for(i = 0; i < context->numPorts; i++)
   {
      
      port = &context->ports[i];

      
      rstpPtiInit(port);
      
      rstpPrxInit(port);
      
      rstpPpmInit(port);
      
      rstpBdmInit(port);
      
      rstpPtxInit(port);
      
      rstpPimInit(port);
      
      rstpPrtInit(port);
      
      rstpPstInit(port);
      
      rstpTcmInit(port);
   }

   
   rstpFsm(context);
}




void rstpFsm(RstpBridgeContext *context)
{
   uint_t i;
   RstpBridgePort *port;

   
   
   do
   {
      
      context->busy = FALSE;

      
      
      rstpPrsFsm(context);

      
      
      for(i = 0; i < context->numPorts; i++)
      {
         
         port = &context->ports[i];

         
         rstpPtiFsm(port);
         
         rstpPrxFsm(port);
         
         rstpPpmFsm(port);
         
         rstpBdmFsm(port);
         
         rstpPimFsm(port);
         
         rstpPrtFsm(port);
         
         rstpPstFsm(port);
         
         rstpTcmFsm(port);

         
         
         if(port->fdbFlush)
         {
            
            rstpRemoveFdbEntries(port);
         }
      }

      
      if(!context->busy)
      {
         
         for(i = 0; i < context->numPorts; i++)
         {
            
            port = &context->ports[i];

            
            rstpPtxFsm(port);
         }
      }

      
      
   } while(context->busy);
}




void rstpFsmError(RstpBridgeContext *context)
{
   
   TRACE_ERROR("RSTP finite state machine error!\r\n");
}

#endif
