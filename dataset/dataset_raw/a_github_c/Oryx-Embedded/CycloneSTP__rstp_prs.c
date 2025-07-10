


#define TRACE_LEVEL RSTP_TRACE_LEVEL


#include "rstp/rstp.h"
#include "rstp/rstp_fsm.h"
#include "rstp/rstp_prs.h"
#include "rstp/rstp_procedures.h"
#include "rstp/rstp_misc.h"
#include "debug.h"


#if (RSTP_SUPPORT == ENABLED)


const RstpParamName rstpPrsStates[] =
{
   {RSTP_PRS_STATE_INIT_BRIDGE,    "INIT_BRIDGE"},
   {RSTP_PRS_STATE_ROLE_SELECTION, "ROLE_SELECTION"}
};




void rstpPrsInit(RstpBridgeContext *context)
{
   
   rstpPrsChangeState(context, RSTP_PRS_STATE_INIT_BRIDGE);
}




void rstpPrsFsm(RstpBridgeContext *context)
{
   uint_t i;
   bool_t reselect;

   
   
   switch(context->prsState)
   {
   
   case RSTP_PRS_STATE_INIT_BRIDGE:
      
      rstpPrsChangeState(context, RSTP_PRS_STATE_ROLE_SELECTION);
      break;

   
   case RSTP_PRS_STATE_ROLE_SELECTION:
      
      for(reselect = FALSE, i = 0; i < context->numPorts; i++)
      {
         reselect |= context->ports[i].reselect;
      }

      
      
      if(reselect)
      {
         rstpPrsChangeState(context, RSTP_PRS_STATE_ROLE_SELECTION);
      }

      break;

   
   default:
      
      rstpFsmError(context);
      break;
   }
}




void rstpPrsChangeState(RstpBridgeContext *context, RstpPrsState newState)
{
   
   TRACE_VERBOSE("PRS state machine %s -> %s\r\n",
      rstpGetParamName(context->prsState, rstpPrsStates, arraysize(rstpPrsStates)),
      rstpGetParamName(newState, rstpPrsStates, arraysize(rstpPrsStates)));

   
   context->prsState = newState;

   
   
   switch(context->prsState)
   {
   
   case RSTP_PRS_STATE_INIT_BRIDGE:
      
      rstpUpdtRoleDisabledTree(context);
      break;

   
   case RSTP_PRS_STATE_ROLE_SELECTION:
      
      rstpClearReselectTree(context);
      rstpUpdtRolesTree(context);
      rstpSetSelectedTree(context);
      break;

   
   default:
      
      break;
   }

   
   context->busy = TRUE;
}

#endif
