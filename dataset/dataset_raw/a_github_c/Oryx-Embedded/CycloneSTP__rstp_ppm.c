


#define TRACE_LEVEL RSTP_TRACE_LEVEL


#include "rstp/rstp.h"
#include "rstp/rstp_fsm.h"
#include "rstp/rstp_ppm.h"
#include "rstp/rstp_conditions.h"
#include "rstp/rstp_misc.h"
#include "debug.h"


#if (RSTP_SUPPORT == ENABLED)


const RstpParamName rstpPpmStates[] =
{
   {RSTP_PPM_STATE_CHECKING_RSTP, "CHECKING_RSTP"},
   {RSTP_PPM_STATE_SELECTING_STP, "SELECTING_STP"},
   {RSTP_PPM_STATE_SENSING,       "SENSING"}
};




void rstpPpmInit(RstpBridgePort *port)
{
   
   rstpPpmChangeState(port, RSTP_PPM_STATE_CHECKING_RSTP);
}




void rstpPpmFsm(RstpBridgePort *port)
{
   
   
   switch(port->ppmState)
   {
   
   case RSTP_PPM_STATE_CHECKING_RSTP:
      
      if(port->mdelayWhile == 0)
      {
         
         rstpPpmChangeState(port, RSTP_PPM_STATE_SENSING);
      }
      else if(port->mdelayWhile != rstpMigrateTime(port->context) &&
         !port->portEnabled)
      {
         
         rstpPpmChangeState(port, RSTP_PPM_STATE_CHECKING_RSTP);
      }
      else
      {
         
      }

      break;

   
   case RSTP_PPM_STATE_SELECTING_STP:
      
      if(port->mdelayWhile == 0 || !port->portEnabled || port->mcheck)
      {
         
         rstpPpmChangeState(port, RSTP_PPM_STATE_SENSING);
      }

      break;

   
   case RSTP_PPM_STATE_SENSING:
      
      if(port->sendRstp && port->rcvdStp)
      {
         
         rstpPpmChangeState(port, RSTP_PPM_STATE_SELECTING_STP);
      }
      else if(!port->portEnabled || port->mcheck ||
         (rstpVersion(port->context) && !port->sendRstp && port->rcvdRstp))
      {
         
         rstpPpmChangeState(port, RSTP_PPM_STATE_CHECKING_RSTP);
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




void rstpPpmChangeState(RstpBridgePort *port, RstpPpmState newState)
{
   
   TRACE_VERBOSE("Port %" PRIu8 ": PPM state machine %s -> %s\r\n",
      port->portIndex,
      rstpGetParamName(port->ppmState, rstpPpmStates, arraysize(rstpPpmStates)),
      rstpGetParamName(newState, rstpPpmStates, arraysize(rstpPpmStates)));

   
   port->ppmState = newState;

   
   
   switch(port->ppmState)
   {
   
   case RSTP_PPM_STATE_CHECKING_RSTP:
      
      port->mcheck = FALSE;

      
      
      
      port->sendRstp = rstpVersion(port->context);

      
      port->mdelayWhile = rstpMigrateTime(port->context);
      break;

   
   case RSTP_PPM_STATE_SELECTING_STP:
      
      port->sendRstp = FALSE;

      
      port->mdelayWhile = rstpMigrateTime(port->context);
      break;

   
   case RSTP_PPM_STATE_SENSING:
      
      port->rcvdRstp = FALSE;
      port->rcvdStp = FALSE;
      break;

   
   default:
      
      break;
   }

   
   port->context->busy = TRUE;
}

#endif
