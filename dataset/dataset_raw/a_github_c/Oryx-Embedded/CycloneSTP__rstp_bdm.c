


#define TRACE_LEVEL RSTP_TRACE_LEVEL


#include "rstp/rstp.h"
#include "rstp/rstp_fsm.h"
#include "rstp/rstp_bdm.h"
#include "rstp/rstp_conditions.h"
#include "rstp/rstp_misc.h"
#include "debug.h"


#if (RSTP_SUPPORT == ENABLED)


const RstpParamName rstpBdmStates[] =
{
   {RSTP_BDM_STATE_EDGE,     "EDGE"},
   {RSTP_BDM_STATE_NOT_EDGE, "NOT_EDGE"}
};




void rstpBdmInit(RstpBridgePort *port)
{
   
   if(rstpAdminEdge(port))
   {
      rstpBdmChangeState(port, RSTP_BDM_STATE_EDGE);
   }
   else
   {
      rstpBdmChangeState(port, RSTP_BDM_STATE_NOT_EDGE);
   }
}




void rstpBdmFsm(RstpBridgePort *port)
{
   
   
   switch(port->bdmState)
   {
   
   case RSTP_BDM_STATE_EDGE:
      
      if((!port->portEnabled && !rstpAdminEdge(port)) || !port->operEdge)
      {
         
         rstpBdmChangeState(port, RSTP_BDM_STATE_NOT_EDGE);
      }

      break;

   
   case RSTP_BDM_STATE_NOT_EDGE:
      
      if((!port->portEnabled && rstpAdminEdge(port)) ||
         (port->edgeDelayWhile == 0 && rstpAutoEdge(port) &&
         port->sendRstp && port->proposing))
      {
         
         rstpBdmChangeState(port, RSTP_BDM_STATE_EDGE);
      }

      break;

   
   default:
      
      rstpFsmError(port->context);
      break;
   }
}




void rstpBdmChangeState(RstpBridgePort *port, RstpBdmState newState)
{
   
   TRACE_VERBOSE("Port %" PRIu8 ": BDM state machine %s -> %s\r\n",
      port->portIndex,
      rstpGetParamName(port->bdmState, rstpBdmStates, arraysize(rstpBdmStates)),
      rstpGetParamName(newState, rstpBdmStates, arraysize(rstpBdmStates)));

   
   port->bdmState = newState;

   
   
   switch(port->bdmState)
   {
   
   case RSTP_BDM_STATE_EDGE:
      
      port->operEdge = TRUE;
      break;

   
   case RSTP_BDM_STATE_NOT_EDGE:
      
      port->operEdge = FALSE;
      break;

   
   default:
      
      break;
   }

   
   port->context->busy = TRUE;
}

#endif
