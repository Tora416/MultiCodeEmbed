


#define TRACE_LEVEL RSTP_TRACE_LEVEL


#include "rstp/rstp.h"
#include "rstp/rstp_fsm.h"
#include "rstp/rstp_prx.h"
#include "rstp/rstp_procedures.h"
#include "rstp/rstp_conditions.h"
#include "rstp/rstp_misc.h"
#include "debug.h"


#if (RSTP_SUPPORT == ENABLED)


const RstpParamName rstpPrxStates[] =
{
   {RSTP_PRX_STATE_DISCARD, "DISCARD"},
   {RSTP_PRX_STATE_RECEIVE, "RECEIVE"}
};




void rstpPrxInit(RstpBridgePort *port)
{
   
   rstpPrxChangeState(port, RSTP_PRX_STATE_DISCARD);
}




void rstpPrxFsm(RstpBridgePort *port)
{
   
   if((port->rcvdBpdu || port->edgeDelayWhile != rstpMigrateTime(port->context)) &&
      !port->portEnabled)
   {
      
      
      rstpPrxChangeState(port, RSTP_PRX_STATE_DISCARD);
   }
   else
   {
      
      
      switch(port->prxState)
      {
      
      case RSTP_PRX_STATE_DISCARD:
         
         if(port->rcvdBpdu && port->portEnabled)
         {
            
            rstpPrxChangeState(port, RSTP_PRX_STATE_RECEIVE);
         }

         break;

      
      case RSTP_PRX_STATE_RECEIVE:
         
         if(port->rcvdBpdu && port->portEnabled && !port->rcvdMsg)
         {
            
            rstpPrxChangeState(port, RSTP_PRX_STATE_RECEIVE);
         }

         break;

      
      default:
         
         rstpFsmError(port->context);
         break;
      }
   }
}




void rstpPrxChangeState(RstpBridgePort *port, RstpPrxState newState)
{
   
   TRACE_VERBOSE("Port %" PRIu8 ": PRX state machine %s -> %s\r\n",
      port->portIndex,
      rstpGetParamName(port->prxState, rstpPrxStates, arraysize(rstpPrxStates)),
      rstpGetParamName(newState, rstpPrxStates, arraysize(rstpPrxStates)));

   
   port->prxState = newState;

   
   
   switch(port->prxState)
   {
   
   case RSTP_PRX_STATE_DISCARD:
      
      port->rcvdBpdu = FALSE;
      port->rcvdRstp = FALSE;
      port->rcvdStp = FALSE;
      port->rcvdMsg = FALSE;

      
      port->edgeDelayWhile = rstpMigrateTime(port->context);
      break;

   
   case RSTP_PRX_STATE_RECEIVE:
      
      
      rstpUpdtBpduVersion(port);
      port->operEdge = FALSE;
      port->rcvdBpdu = FALSE;

      
      
      port->rcvdMsg = TRUE;

      
      port->edgeDelayWhile = rstpMigrateTime(port->context);
      break;

   
   default:
      
      break;
   }

   
   port->context->busy = TRUE;
}

#endif
