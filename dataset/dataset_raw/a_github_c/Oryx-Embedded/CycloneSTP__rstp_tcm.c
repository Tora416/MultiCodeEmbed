


#define TRACE_LEVEL RSTP_TRACE_LEVEL


#include "rstp/rstp.h"
#include "rstp/rstp_fsm.h"
#include "rstp/rstp_tcm.h"
#include "rstp/rstp_procedures.h"
#include "rstp/rstp_misc.h"
#include "debug.h"


#if (RSTP_SUPPORT == ENABLED)


const RstpParamName rstpTcmStates[] =
{
   {RSTP_TCM_STATE_INACTIVE,     "INACTIVE"},
   {RSTP_TCM_STATE_LEARNING,     "LEARNING"},
   {RSTP_TCM_STATE_DETECTED,     "DETECTED"},
   {RSTP_TCM_STATE_NOTIFIED_TCN, "NOTIFIED_TCN"},
   {RSTP_TCM_STATE_NOTIFIED_TC,  "NOTIFIED_TC"},
   {RSTP_TCM_STATE_PROPAGATING,  "PROPAGATING"},
   {RSTP_TCM_STATE_ACKNOWLEDGED, "ACKNOWLEDGED"},
   {RSTP_TCM_STATE_ACTIVE,       "ACTIVE"}
};




void rstpTcmInit(RstpBridgePort *port)
{
   
   rstpTcmChangeState(port, RSTP_TCM_STATE_INACTIVE);
}




void rstpTcmFsm(RstpBridgePort *port)
{
   
   
   switch(port->tcmState)
   {
   
   case RSTP_TCM_STATE_INACTIVE:
      
      if(port->learn && !port->fdbFlush)
      {
         
         rstpTcmChangeState(port, RSTP_TCM_STATE_LEARNING);
      }

      break;

   
   case RSTP_TCM_STATE_LEARNING:
      
      if(port->rcvdTc || port->rcvdTcn || port->rcvdTcAck || port->tcProp)
      {
         
         rstpTcmChangeState(port, RSTP_TCM_STATE_LEARNING);
      }
      else if((port->role == STP_PORT_ROLE_ROOT ||
         port->role == STP_PORT_ROLE_DESIGNATED) &&
         port->forward && !port->operEdge)
      {
         
         rstpTcmChangeState(port, RSTP_TCM_STATE_DETECTED);
      }
      else if(port->role != STP_PORT_ROLE_ROOT &&
         port->role != STP_PORT_ROLE_DESIGNATED &&
         !(port->learn || port->learning) &&
         !(port->rcvdTc || port->rcvdTcn || port->rcvdTcAck || port->tcProp))
      {
         
         rstpTcmChangeState(port, RSTP_TCM_STATE_INACTIVE);
      }
      else
      {
         
      }

      break;

   
   case RSTP_TCM_STATE_NOTIFIED_TCN:
      
      rstpTcmChangeState(port, RSTP_TCM_STATE_NOTIFIED_TC);
      break;

   
   case RSTP_TCM_STATE_DETECTED:
   case RSTP_TCM_STATE_NOTIFIED_TC:
   case RSTP_TCM_STATE_PROPAGATING:
   case RSTP_TCM_STATE_ACKNOWLEDGED:
      
      rstpTcmChangeState(port, RSTP_TCM_STATE_ACTIVE);
      break;

   
   case RSTP_TCM_STATE_ACTIVE:
      
      if((port->role != STP_PORT_ROLE_ROOT &&
         port->role != STP_PORT_ROLE_DESIGNATED) || port->operEdge)
      {
         
         rstpTcmChangeState(port, RSTP_TCM_STATE_LEARNING);
      }
      else if(port->rcvdTcn)
      {
         
         rstpTcmChangeState(port, RSTP_TCM_STATE_NOTIFIED_TCN);
      }
      else if(port->rcvdTc)
      {
         
         rstpTcmChangeState(port, RSTP_TCM_STATE_NOTIFIED_TC);
      }
      else if(port->tcProp && !port->operEdge)
      {
         
         rstpTcmChangeState(port, RSTP_TCM_STATE_PROPAGATING);
      }
      else if(port->rcvdTcAck)
      {
         
         rstpTcmChangeState(port, RSTP_TCM_STATE_ACKNOWLEDGED);
      }
      else
      {
         
      }

      break;

   
   default:
      
      rstpFsmError(port->context);
      break;
   }
}




void rstpTcmChangeState(RstpBridgePort *port, RstpTcmState newState)
{
   
   TRACE_VERBOSE("Port %" PRIu8 ": TCM state machine %s -> %s\r\n",
      port->portIndex,
      rstpGetParamName(port->tcmState, rstpTcmStates, arraysize(rstpTcmStates)),
      rstpGetParamName(newState, rstpTcmStates, arraysize(rstpTcmStates)));

   
   port->tcmState = newState;

   
   
   switch(port->tcmState)
   {
   
   case RSTP_TCM_STATE_INACTIVE:
      port->fdbFlush = TRUE;
      port->tcWhile = 0;
      port->tcAck = FALSE;
      break;

   
   case RSTP_TCM_STATE_LEARNING:
      port->rcvdTc = FALSE;
      port->rcvdTcn = FALSE;
      port->rcvdTcAck = FALSE;
      port->tcProp = FALSE;
      break;

   
   case RSTP_TCM_STATE_DETECTED:
      rstpNewTcWhile(port);
      rstpSetTcPropTree(port);
      port->newInfo = TRUE;
      break;

   
   case RSTP_TCM_STATE_NOTIFIED_TCN:
      rstpNewTcWhile(port);
      break;

   
   case RSTP_TCM_STATE_NOTIFIED_TC:
      port->rcvdTcn = FALSE;
      port->rcvdTc = FALSE;

      if(port->role == STP_PORT_ROLE_DESIGNATED)
      {
         port->tcAck = TRUE;
      }

      
      rstpSetTcPropTree(port);
      break;

   
   case RSTP_TCM_STATE_PROPAGATING:
      rstpNewTcWhile(port);
      port->fdbFlush = TRUE;
      port->tcProp = FALSE;
      break;

   
   case RSTP_TCM_STATE_ACKNOWLEDGED:
      port->tcWhile = 0;
      port->rcvdTcAck = FALSE;
      break;

   
   case RSTP_TCM_STATE_ACTIVE:
      
      break;

   
   default:
      
      break;
   }

   
   port->context->busy = TRUE;
}

#endif
