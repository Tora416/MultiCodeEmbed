


#define TRACE_LEVEL RSTP_TRACE_LEVEL


#include "rstp/rstp.h"
#include "rstp/rstp_fsm.h"
#include "rstp/rstp_pti.h"
#include "rstp/rstp_misc.h"
#include "debug.h"


#if (RSTP_SUPPORT == ENABLED)


const RstpParamName rstpPtiStates[] =
{
   {RSTP_PTI_STATE_ONE_SECOND, "ONE_SECOND"},
   {RSTP_PTI_STATE_TICK,       "TICK"}
};




void rstpPtiInit(RstpBridgePort *port)
{
   
   
   rstpPtiChangeState(port, RSTP_PTI_STATE_ONE_SECOND);
}




void rstpPtiFsm(RstpBridgePort *port)
{
   
   
   switch(port->ptiState)
   {
   
   case RSTP_PTI_STATE_ONE_SECOND:
      
      if(port->tick)
      {
         rstpPtiChangeState(port, RSTP_PTI_STATE_TICK);
      }

      break;

   
   case RSTP_PTI_STATE_TICK:
      
      
      rstpPtiChangeState(port, RSTP_PTI_STATE_ONE_SECOND);
      break;

   
   default:
      
      rstpFsmError(port->context);
      break;
   }
}




void rstpPtiChangeState(RstpBridgePort *port, RstpPtiState newState)
{
   
   TRACE_VERBOSE("Port %" PRIu8 ": PTI state machine %s -> %s\r\n",
      port->portIndex,
      rstpGetParamName(port->ptiState, rstpPtiStates, arraysize(rstpPtiStates)),
      rstpGetParamName(newState, rstpPtiStates, arraysize(rstpPtiStates)));

   
   port->ptiState = newState;

   
   
   switch(port->ptiState)
   {
   
   case RSTP_PTI_STATE_ONE_SECOND:
      
      port->tick = FALSE;
      break;

   
   case RSTP_PTI_STATE_TICK:
      
      rstpDecrementTimer(&port->helloWhen);
      rstpDecrementTimer(&port->tcWhile);
      rstpDecrementTimer(&port->fdWhile);
      rstpDecrementTimer(&port->rcvdInfoWhile);
      rstpDecrementTimer(&port->rrWhile);
      rstpDecrementTimer(&port->rbWhile);
      rstpDecrementTimer(&port->mdelayWhile);
      rstpDecrementTimer(&port->edgeDelayWhile);
      rstpDecrementTimer(&port->txCount);
      break;

   
   default:
      
      break;
   }

   
   port->context->busy = TRUE;
}

#endif
