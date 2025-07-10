


#define TRACE_LEVEL STP_TRACE_LEVEL


#include "stp/stp.h"
#include "stp/stp_operation.h"
#include "stp/stp_procedures.h"
#include "stp/stp_conditions.h"
#include "stp/stp_misc.h"
#include "debug.h"


#if (STP_SUPPORT == ENABLED)




void stpReceivedConfigBpdu(StpBridgePort *port, const StpBpdu *bpdu)
{
   bool_t rootBridge;
   StpBridgeContext *context;

   
   context = port->context;

   
   if(port->state != STP_PORT_STATE_DISABLED && port->macOperState)
   {
      
      
      if(stpSupersedesPortInfo(port, bpdu))
      {
         
         rootBridge = stpRootBridge(context);

         
         stpRecordConfigInfo(port, bpdu);
         
         stpConfigUpdate(context);
         
         stpPortStateSelection(context);

         
         
         if(rootBridge && !stpRootBridge(context))
         {
            
            stpStopTimer(&context->helloTimer);

            
            if(context->topologyChangeDetected)
            {
               
               
               
               stpStopTimer(&context->topologyChangeTimer);
               stpTransmitTcnBpdu(context);
               stpStartTimer(&context->tcnTimer, 0);
            }
         }

         
         if(stpRootPort(port))
         {
            
            
            stpRecordConfigTimeoutValues(context, bpdu);
            stpConfigBpduGeneration(context);

            
            if((bpdu->flags & STP_BPDU_FLAG_TC_ACK) != 0)
            {
               
               stpTopologyChangeAcked(context);
            }
         }
      }
      else
      {
         
         
         
         
         if(stpDesignatedPort(port))
         {
            stpReplyToConfigBpdu(port);
         }
      }
   }
}




void stpReceivedTcnBpdu(StpBridgePort *port, const StpBpdu *bpdu)
{
   
   if(port->state != STP_PORT_STATE_DISABLED && port->macOperState)
   {
      
      
      if(stpDesignatedPort(port))
      {
         
         stpTopologyChangeDetection(port->context);
         
         stpAckTopologyChange(port);
      }
   }
}




void stpHelloTimerExpiry(StpBridgeContext *context)
{
   
   
   stpConfigBpduGeneration(context);
   stpStartTimer(&context->helloTimer, 0);
}




void stpMessageAgeTimerExpiry(StpBridgePort *port)
{
   bool_t rootBridge;
   StpBridgeContext *context;

   
   context = port->context;

   
   rootBridge = stpRootBridge(context);

   
   
   stpBecomeDesignatedPort(port);

   
   stpConfigUpdate(context);
   
   stpPortStateSelection(context);

   
   if(!rootBridge && stpRootBridge(context))
   {
      
      
      
      context->maxAge = context->bridgeMaxAge;
      context->helloTime = context->bridgeHelloTime;
      context->forwardDelay = context->bridgeForwardDelay;

      
      stpTopologyChangeDetection(context);
      
      stpStopTimer(&context->tcnTimer);

      
      
      stpConfigBpduGeneration(context);
      stpStartTimer(&context->helloTimer, 0);
   }
}




void stpForwardDelayTimerExpiry(StpBridgePort *port)
{
   StpBridgeContext *context;

   
   context = port->context;

   
   if(port->state == STP_PORT_STATE_LISTENING)
   {
      
      
      stpUpdatePortState(port, STP_PORT_STATE_LEARNING);

      
      stpStartTimer(&port->forwardDelayTimer, 0);
   }
   else if(port->state == STP_PORT_STATE_LEARNING)
   {
      
      
      stpUpdatePortState(port, STP_PORT_STATE_FORWARDING);

      
      
      
      if(stpDesignatedBridge(context) && port->changeDetectionEnabled)
      {
         
         stpTopologyChangeDetection(context);
      }
   }
   else
   {
      
   }
}




void stpTcnTimerExpiry(StpBridgeContext *context)
{
   
   stpTransmitTcnBpdu(context);
   
   stpStartTimer(&context->tcnTimer, 0);
}




void stpTopologyChangeTimerExpiry(StpBridgeContext *context)
{
   
   context->topologyChangeDetected = FALSE;
   
   stpUpdateTopologyChange(context, FALSE);
}




void stpHoldTimerExpiry(StpBridgePort *port)
{
   
   
   
   if(port->configPending)
   {
      stpTransmitConfigBpdu(port);
   }
}

#endif
