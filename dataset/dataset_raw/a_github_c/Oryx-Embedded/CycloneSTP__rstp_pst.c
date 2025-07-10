


#define TRACE_LEVEL RSTP_TRACE_LEVEL


#include "rstp/rstp.h"
#include "rstp/rstp_fsm.h"
#include "rstp/rstp_pst.h"
#include "rstp/rstp_procedures.h"
#include "rstp/rstp_misc.h"
#include "debug.h"


#if (RSTP_SUPPORT == ENABLED)


const RstpParamName rstpPstStates[] =
{
   {RSTP_PST_STATE_DISCARDING, "DISCARDING"},
   {RSTP_PST_STATE_LEARNING,   "LEARNING"},
   {RSTP_PST_STATE_FORWARDING, "FORWARDING"}
};




void rstpPstInit(RstpBridgePort *port)
{
   
   rstpPstChangeState(port, RSTP_PST_STATE_DISCARDING);
}




void rstpPstFsm(RstpBridgePort *port)
{
   
   
   switch(port->pstState)
   {
   
   case RSTP_PST_STATE_DISCARDING:
      
      if(port->learn)
      {
         
         rstpPstChangeState(port, RSTP_PST_STATE_LEARNING);
      }

      break;

   
   case RSTP_PST_STATE_LEARNING:
      
      if(port->forward)
      {
         
         rstpPstChangeState(port, RSTP_PST_STATE_FORWARDING);
      }
      else if(!port->learn)
      {
         
         rstpPstChangeState(port, RSTP_PST_STATE_DISCARDING);
      }
      else
      {
         
      }

      break;

   
   case RSTP_PST_STATE_FORWARDING:
      
      if(!port->forward)
      {
         
         rstpPstChangeState(port, RSTP_PST_STATE_DISCARDING);
      }

      break;

   
   default:
      
      rstpFsmError(port->context);
      break;
   }
}




void rstpPstChangeState(RstpBridgePort *port, RstpPstState newState)
{
   
   TRACE_VERBOSE("Port %" PRIu8 ": PST state machine %s -> %s\r\n",
      port->portIndex,
      rstpGetParamName(port->pstState, rstpPstStates, arraysize(rstpPstStates)),
      rstpGetParamName(newState, rstpPstStates, arraysize(rstpPstStates)));

   
   port->pstState = newState;

   
   
   switch(port->pstState)
   {
   
   case RSTP_PST_STATE_DISCARDING:
      
      rstpDisableLearning(port);
      port->learning = FALSE;
      rstpDisableForwarding(port);
      port->forwarding = FALSE;
      break;

   
   case RSTP_PST_STATE_LEARNING:
      
      rstpEnableLearning(port);
      port->learning = TRUE;
      break;

   
   case RSTP_PST_STATE_FORWARDING:
      
      rstpEnableForwarding(port);
      port->forwarding = TRUE;
      break;

   
   default:
      
      break;
   }

   
   port->context->busy = TRUE;
}

#endif
