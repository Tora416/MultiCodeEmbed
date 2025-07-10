


#define TRACE_LEVEL RSTP_TRACE_LEVEL


#include "rstp/rstp.h"
#include "rstp/rstp_fsm.h"
#include "rstp/rstp_ptx.h"
#include "rstp/rstp_procedures.h"
#include "rstp/rstp_conditions.h"
#include "rstp/rstp_misc.h"
#include "debug.h"


#if (RSTP_SUPPORT == ENABLED)


const RstpParamName rstpPtxStates[] =
{
   {RSTP_PTX_STATE_TRANSMIT_INIT,     "TRANSMIT_INIT"},
   {RSTP_PTX_STATE_TRANSMIT_PERIODIC, "TRANSMIT_PERIODIC"},
   {RSTP_PTX_STATE_TRANSMIT_CONFIG,   "TRANSMIT_CONFIG"},
   {RSTP_PTX_STATE_TRANSMIT_TCN,      "TRANSMIT_TCN"},
   {RSTP_PTX_STATE_TRANSMIT_RSTP,     "TRANSMIT_RSTP"},
   {RSTP_PTX_STATE_IDLE,              "IDLE"}
};




void rstpPtxInit(RstpBridgePort *port)
{
   
   rstpPtxChangeState(port, RSTP_PTX_STATE_TRANSMIT_INIT);
}




void rstpPtxFsm(RstpBridgePort *port)
{
   RstpBridgeContext *context;

   
   context = port->context;

   
   if(!port->portEnabled)
   {
      
      
      rstpPtxChangeState(port, RSTP_PTX_STATE_TRANSMIT_INIT);
   }
   else
   {
      
      
      switch(port->ptxState)
      {
      
      
      case RSTP_PTX_STATE_TRANSMIT_INIT:
      case RSTP_PTX_STATE_TRANSMIT_PERIODIC:
      case RSTP_PTX_STATE_TRANSMIT_CONFIG:
      case RSTP_PTX_STATE_TRANSMIT_TCN:
      case RSTP_PTX_STATE_TRANSMIT_RSTP:
         
         rstpPtxChangeState(port, RSTP_PTX_STATE_IDLE);
         break;

      
      case RSTP_PTX_STATE_IDLE:
         
         if(port->selected && !port->updtInfo)
         {
            
            
            if(port->helloWhen == 0)
            {
               
               rstpPtxChangeState(port, RSTP_PTX_STATE_TRANSMIT_PERIODIC);
            }
            else
            {
               
               if(port->newInfo)
               {
                  
                  if(port->txCount < rstpTxHoldCount(context))
                  {
                     
                     if(port->sendRstp)
                     {
                        
                        rstpPtxChangeState(port, RSTP_PTX_STATE_TRANSMIT_RSTP);
                     }
                     else
                     {
                        
                        if(port->role == STP_PORT_ROLE_ROOT)
                        {
                           
                           rstpPtxChangeState(port, RSTP_PTX_STATE_TRANSMIT_TCN);
                        }
                        else if(port->role == STP_PORT_ROLE_DESIGNATED)
                        {
                           
                           rstpPtxChangeState(port, RSTP_PTX_STATE_TRANSMIT_CONFIG);
                        }
                        else
                        {
                           
                        }
                     }
                  }
               }
            }
         }

         break;

      
      default:
         
         rstpFsmError(port->context);
         break;
      }
   }
}




void rstpPtxChangeState(RstpBridgePort *port, RstpPtxState newState)
{
   
   if(port->ptxState != newState)
   {
      
      TRACE_VERBOSE("Port %" PRIu8 ": PTX state machine %s -> %s\r\n",
         port->portIndex,
         rstpGetParamName(port->ptxState, rstpPtxStates, arraysize(rstpPtxStates)),
         rstpGetParamName(newState, rstpPtxStates, arraysize(rstpPtxStates)));
   }

   
   port->ptxState = newState;

   
   
   switch(port->ptxState)
   {
   
   case RSTP_PTX_STATE_TRANSMIT_INIT:
      
      port->newInfo = TRUE;
      port->txCount = 0;
      break;

   
   case RSTP_PTX_STATE_TRANSMIT_PERIODIC:
      
      if(port->role == STP_PORT_ROLE_DESIGNATED)
      {
         
         port->newInfo = TRUE;
      }
      else if(port->role == STP_PORT_ROLE_ROOT)
      {
         
         if(port->tcWhile != 0)
         {
            
            port->newInfo = TRUE;
         }
      }
      else
      {
         
      }

      break;

   
   case RSTP_PTX_STATE_TRANSMIT_CONFIG:
      
      port->newInfo = FALSE;
      rstpTxConfig(port);
      port->txCount++;
      port->tcAck = FALSE;
      break;

   
   case RSTP_PTX_STATE_TRANSMIT_TCN:
      
      port->newInfo = FALSE;
      rstpTxTcn(port);
      port->txCount++;
      break;

   
   case RSTP_PTX_STATE_TRANSMIT_RSTP:
      
      port->newInfo = FALSE;
      rstpTxRstp(port);
      port->txCount++;
      port->tcAck = FALSE;
      break;

   
   case RSTP_PTX_STATE_IDLE:
      
      port->helloWhen = rstpHelloTime(port);
      break;

   
   default:
      
      break;
   }

   
   if(port->portEnabled)
   {
      
      port->context->busy = TRUE;
   }
}

#endif
