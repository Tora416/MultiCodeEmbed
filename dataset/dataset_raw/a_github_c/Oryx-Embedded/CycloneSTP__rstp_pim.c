


#define TRACE_LEVEL RSTP_TRACE_LEVEL


#include "rstp/rstp.h"
#include "rstp/rstp_fsm.h"
#include "rstp/rstp_pim.h"
#include "rstp/rstp_procedures.h"
#include "rstp/rstp_misc.h"
#include "debug.h"


#if (RSTP_SUPPORT == ENABLED)


const RstpParamName rstpPimStates[] =
{
   {RSTP_PIM_STATE_DISABLED,            "DISABLED"},
   {RSTP_PIM_STATE_AGED,                "AGED"},
   {RSTP_PIM_STATE_UPDATE,              "UPDATE"},
   {RSTP_PIM_STATE_SUPERIOR_DESIGNATED, "SUPERIOR_DESIGNATED"},
   {RSTP_PIM_STATE_REPEATED_DESIGNATED, "REPEATED_DESIGNATED"},
   {RSTP_PIM_STATE_INFERIOR_DESIGNATED, "INFERIOR_DESIGNATED"},
   {RSTP_PIM_STATE_NOT_DESIGNATED,      "NOT_DESIGNATED"},
   {RSTP_PIM_STATE_OTHER,               "OTHER"},
   {RSTP_PIM_STATE_CURRENT,             "CURRENT"},
   {RSTP_PIM_STATE_RECEIVE,             "RECEIVE"}
};




void rstpPimInit(RstpBridgePort *port)
{
   
   rstpPimChangeState(port, RSTP_PIM_STATE_DISABLED);
}




void rstpPimFsm(RstpBridgePort *port)
{
   
   if(!port->portEnabled && port->infoIs != RSTP_INFO_IS_DISABLED)
   {
      
      
      rstpPimChangeState(port, RSTP_PIM_STATE_DISABLED);
   }
   else
   {
      
      
      switch(port->pimState)
      {
      
      case RSTP_PIM_STATE_DISABLED:
         
         if(port->rcvdMsg)
         {
            
            rstpPimChangeState(port, RSTP_PIM_STATE_DISABLED);
         }
         else if(port->portEnabled)
         {
            
            rstpPimChangeState(port, RSTP_PIM_STATE_AGED);
         }
         else
         {
            
         }

         break;

      
      case RSTP_PIM_STATE_AGED:
         
         if(port->selected && port->updtInfo)
         {
            
            rstpPimChangeState(port, RSTP_PIM_STATE_UPDATE);
         }

         break;

      
      
      case RSTP_PIM_STATE_UPDATE:
      case RSTP_PIM_STATE_SUPERIOR_DESIGNATED:
      case RSTP_PIM_STATE_REPEATED_DESIGNATED:
      case RSTP_PIM_STATE_INFERIOR_DESIGNATED:
      case RSTP_PIM_STATE_NOT_DESIGNATED:
      case RSTP_PIM_STATE_OTHER:
         
         rstpPimChangeState(port, RSTP_PIM_STATE_CURRENT);
         break;

      
      case RSTP_PIM_STATE_CURRENT:
         
         if(port->selected && port->updtInfo)
         {
            
            rstpPimChangeState(port, RSTP_PIM_STATE_UPDATE);
         }
         else if(port->infoIs == RSTP_INFO_IS_RECEIVED &&
            port->rcvdInfoWhile == 0 && !port->updtInfo && !port->rcvdMsg)
         {
            
            rstpPimChangeState(port, RSTP_PIM_STATE_AGED);
         }
         else if(port->rcvdMsg && !port->updtInfo)
         {
            
            rstpPimChangeState(port, RSTP_PIM_STATE_RECEIVE);
         }
         else
         {
            
         }

         break;

      
      case RSTP_PIM_STATE_RECEIVE:
         
         if(port->rcvdInfo == RSTP_RCVD_INFO_SUPERIOR_DESIGNATED)
         {
            
            rstpPimChangeState(port, RSTP_PIM_STATE_SUPERIOR_DESIGNATED);
         }
         else if(port->rcvdInfo == RSTP_RCVD_INFO_REPEATED_DESIGNATED)
         {
            
            rstpPimChangeState(port, RSTP_PIM_STATE_REPEATED_DESIGNATED);
         }
         else if(port->rcvdInfo == RSTP_RCVD_INFO_INFERIOR_DESIGNATED)
         {
            
            rstpPimChangeState(port, RSTP_PIM_STATE_INFERIOR_DESIGNATED);
         }
         else if(port->rcvdInfo == RSTP_RCVD_INFO_INFERIOR_ROOT_ALTERNATE)
         {
            
            rstpPimChangeState(port, RSTP_PIM_STATE_NOT_DESIGNATED);
         }
         else if(port->rcvdInfo == RSTP_RCVD_INFO_OTHER)
         {
            
            rstpPimChangeState(port, RSTP_PIM_STATE_OTHER);
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
}




void rstpPimChangeState(RstpBridgePort *port, RstpPimState newState)
{
   
   TRACE_VERBOSE("Port %" PRIu8 ": PIM state machine %s -> %s\r\n",
      port->portIndex,
      rstpGetParamName(port->pimState, rstpPimStates, arraysize(rstpPimStates)),
      rstpGetParamName(newState, rstpPimStates, arraysize(rstpPimStates)));

   
   port->pimState = newState;

   
   
   switch(port->pimState)
   {
   
   case RSTP_PIM_STATE_DISABLED:
      
      port->rcvdMsg = FALSE;
      port->proposing = FALSE;
      port->proposed = FALSE;
      port->agree = FALSE;
      port->agreed = FALSE;
      port->rcvdInfoWhile = 0;
      port->infoIs = RSTP_INFO_IS_DISABLED;
      port->reselect = TRUE;
      port->selected = FALSE;
      break;

   
   case RSTP_PIM_STATE_AGED:
      
      port->infoIs = RSTP_INFO_IS_AGED;
      port->reselect = TRUE;
      port->selected = FALSE;
      break;

   
   case RSTP_PIM_STATE_UPDATE:
      port->proposing = FALSE;
      port->proposed = FALSE;

      
      port->agreed = port->agreed &&
         rstpBetterOrSameInfo(port, RSTP_INFO_IS_MINE);

#if defined(RSTP_PIM_WORKAROUND_1)
      
      if(port->forward)
      {
         port->agreed = port->sendRstp;
      }
#endif

      port->synced = port->synced && port->agreed;
      port->portPriority = port->designatedPriority;
      port->portTimes = port->designatedTimes;
      port->updtInfo = FALSE;
      port->infoIs = RSTP_INFO_IS_MINE;
      port->newInfo = TRUE;
      break;

   
   case RSTP_PIM_STATE_SUPERIOR_DESIGNATED:
      port->agreed = FALSE;
      port->proposing = FALSE;
      rstpRecordProposal(port);
      rstpSetTcFlags(port);

      
      port->agree = port->agree &&
         rstpBetterOrSameInfo(port, RSTP_INFO_IS_RECEIVED);

      rstpRecordPriority(port);
      rstpRecordTimes(port);
      rstpUpdtRcvdInfoWhile(port);
      port->infoIs = RSTP_INFO_IS_RECEIVED;
      port->reselect = TRUE;
      port->selected = FALSE;
      port->rcvdMsg = FALSE;
      break;

   
   case RSTP_PIM_STATE_REPEATED_DESIGNATED:
      rstpRecordProposal(port);
      rstpSetTcFlags(port);
      rstpUpdtRcvdInfoWhile(port);
      port->rcvdMsg = FALSE;
      break;

   
   case RSTP_PIM_STATE_INFERIOR_DESIGNATED:
      rstpRecordDispute(port);
      port->rcvdMsg = FALSE;
      break;

   
   case RSTP_PIM_STATE_NOT_DESIGNATED:
      rstpRecordAgreement(port);
      rstpSetTcFlags(port);
      port->rcvdMsg = FALSE;
      break;

   
   case RSTP_PIM_STATE_OTHER:
      port->rcvdMsg = FALSE;
      break;

   
   case RSTP_PIM_STATE_CURRENT:
      
      break;

   
   case RSTP_PIM_STATE_RECEIVE:
      port->rcvdInfo = rstpRcvInfo(port);
      break;

   
   default:
      
      break;
   }

   
   port->context->busy = TRUE;
}

#endif
