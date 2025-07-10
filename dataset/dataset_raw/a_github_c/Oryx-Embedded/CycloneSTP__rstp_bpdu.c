


#define TRACE_LEVEL RSTP_TRACE_LEVEL


#include "rstp/rstp.h"
#include "rstp/rstp_fsm.h"
#include "rstp/rstp_bpdu.h"
#include "rstp/rstp_conditions.h"
#include "rstp/rstp_misc.h"
#include "debug.h"


#if (RSTP_SUPPORT == ENABLED)


const MacAddr RSTP_BRIDGE_GROUP_ADDR = {{{0x01, 0x80, 0xC2, 0x00, 0x00, 0x00}}};


const RstpParamName rstpProtocolVersions[] =
{
   {STP_PROTOCOL_VERSION,  "STP"},
   {RSTP_PROTOCOL_VERSION, "RSTP"}
};


const RstpParamName rstpBpduTypes[] =
{
   {RSTP_BPDU_TYPE_CONFIG, "CONFIG"},
   {RSTP_BPDU_TYPE_TCN,    "TCN"},
   {RSTP_BPDU_TYPE_RST,    "RST"}
};




void rstpProcessLlcFrame(NetInterface *interface, EthHeader *ethHeader,
   const uint8_t *data, size_t length, NetRxAncillary *ancillary, void *param)
{
   const LlcHeader *llcHeader;
   const RstpBpdu *bpdu;
   RstpBridgeContext *context;
   RstpBridgePort *port;

   
   context = (RstpBridgeContext *) param;

   
   
   
   if(!macCompAddr(&ethHeader->destAddr, &RSTP_BRIDGE_GROUP_ADDR))
      return;

   
   if(length < sizeof(LlcHeader))
      return;

   
   llcHeader = (LlcHeader *) data;

   
   
   
   if(llcHeader->dsap != STP_LLC_DSAP || llcHeader->ssap != STP_LLC_SSAP ||
      llcHeader->control != STP_LLC_CTRL)
   {
      return;
   }

   
   if(ancillary->port < 1 || ancillary->port > context->numPorts)
      return;

   
   port = &context->ports[ancillary->port - 1];

   
   bpdu = (RstpBpdu *) (data + sizeof(LlcHeader));

   
   length -= sizeof(LlcHeader);

   
   rstpProcessBpdu(port, bpdu, length);
}




error_t rstpProcessBpdu(RstpBridgePort *port, const RstpBpdu *bpdu,
   size_t length)
{
   error_t error;
   uint8_t bpduType;
   RstpBridgeContext *context;

   
   TRACE_INFO("Port %" PRIu8 ": BPDU received (%" PRIuSIZE " bytes)...\r\n",
      port->portIndex, length);

   
   rstpDumpBpdu(bpdu, length);

   
   context = port->context;

   
   if(length < STP_MIN_BPDU_SIZE)
      return ERROR_INVALID_LENGTH;

   
   if(ntohs(bpdu->protocolId) != STP_PROTOCOL_ID)
      return ERROR_INVALID_LENGTH;

   
   bpduType = bpdu->bpduType;

   
   if(bpduType == RSTP_BPDU_TYPE_CONFIG)
   {
      
      error = rstpValidateConfigBpdu(port, bpdu, length);
      
      if(error)
         return error;

      
      
      length = RSTP_CONFIG_BPDU_SIZE;
   }
   else if(bpduType == RSTP_BPDU_TYPE_TCN)
   {
      
      
      length = RSTP_TCN_BPDU_SIZE;
   }
   else if(bpduType == RSTP_BPDU_TYPE_RST)
   {
      
      
      if(stpVersion(context))
         return ERROR_INVALID_VERSION;

      
      if(length < RSTP_RST_BPDU_SIZE)
         return ERROR_INVALID_LENGTH;

      
      
      length = RSTP_RST_BPDU_SIZE;

      
      if((bpdu->flags & RSTP_BPDU_FLAG_PORT_ROLE) ==
         RSTP_BPDU_FLAG_PORT_ROLE_UNKNOWN)
      {
         
         
         
         bpduType = RSTP_BPDU_TYPE_CONFIG;

         
         error = rstpValidateConfigBpdu(port, bpdu, length);
         
         if(error)
            return error;

         
         
         length = RSTP_CONFIG_BPDU_SIZE;
      }
   }
   else
   {
      
      return ERROR_INVALID_TYPE;
   }

   
   osMemcpy(&context->bpdu, bpdu, length);

   
   context->bpdu.bpduType = bpduType;

   
   
   if(bpduType == RSTP_BPDU_TYPE_CONFIG)
   {
      
      
      
      context->bpdu.flags &= RSTP_BPDU_FLAG_TC_ACK | RSTP_BPDU_FLAG_TC;
   }
   else if(bpduType == RSTP_BPDU_TYPE_RST)
   {
      
      context->bpdu.flags &= ~RSTP_BPDU_FLAG_TC_ACK;
   }
   else
   {
      
      context->bpdu.flags = 0;
   }

   
   
   port->rcvdBpdu = TRUE;

   
   rstpFsm(context);

   
   osMemset(&context->bpdu, 0, sizeof(RstpBpdu));

   
   return NO_ERROR;
}




error_t rstpValidateConfigBpdu(RstpBridgePort *port, const RstpBpdu *bpdu,
   size_t length)
{
   RstpBridgeContext *context;

   
   context = port->context;

   
   if(length < RSTP_CONFIG_BPDU_SIZE)
      return ERROR_INVALID_LENGTH;

   
   if(ntohs(bpdu->messageAge) >= ntohs(bpdu->maxAge))
      return ERROR_INVALID_PACKET;

   
   
   if(rstpCompareBridgeAddr(&bpdu->bridgeId.addr, &context->bridgeId.addr) == 0 &&
      rstpComparePortNum(ntohs(bpdu->portId), port->portId) == 0)
   {
      return ERROR_WRONG_IDENTIFIER;
   }

   
   return NO_ERROR;
}




error_t rstpSendBpdu(RstpBridgePort *port, const RstpBpdu *bpdu,
   size_t length)
{
   error_t error;
   size_t offset;
   LlcHeader *llcHeader;
   NetBuffer *buffer;
   NetTxAncillary ancillary;
   RstpBridgeContext *context;

   
   TRACE_INFO("Port %" PRIu8 ": Sending BPDU (%" PRIuSIZE " bytes)...\r\n",
      port->portIndex, length);

   
   rstpDumpBpdu(bpdu, length);

   
   context = port->context;

   
   buffer = ethAllocBuffer(sizeof(LlcHeader), &offset);

   
   if(buffer != NULL)
   {
      
      llcHeader = netBufferAt(buffer, offset);

      
      
      
      llcHeader->dsap = STP_LLC_DSAP;
      llcHeader->ssap = STP_LLC_SSAP;
      llcHeader->control = STP_LLC_CTRL;

      
      error = netBufferAppend(buffer, bpdu, length);

      
      if(!error)
      {
         
         length += sizeof(LlcHeader);

         
         ancillary = NET_DEFAULT_TX_ANCILLARY;
         
         ancillary.srcMacAddr = port->macAddr;
         
         ancillary.port = port->portIndex;

         
         
         error = ethSendFrame(context->interface, &RSTP_BRIDGE_GROUP_ADDR,
            length, buffer, offset, &ancillary);
      }

      
      netBufferFree(buffer);
   }
   else
   {
      
      error = ERROR_OUT_OF_MEMORY;
   }

   
   return error;
}




error_t rstpDumpBpdu(const RstpBpdu *bpdu, size_t length)
{
#if (RSTP_TRACE_LEVEL >= TRACE_LEVEL_DEBUG)
   uint32_t t;

   
   if(length < STP_MIN_BPDU_SIZE)
      return ERROR_INVALID_LENGTH;

   
   TRACE_DEBUG("  Protocol Identifier = %" PRIu16 "\r\n",
      ntohs(bpdu->protocolId));

   
   TRACE_DEBUG("  Protocol Version Identifier = %" PRIu8 " (%s)\r\n",
      bpdu->protocolVersionId, rstpGetParamName(bpdu->protocolVersionId,
      rstpProtocolVersions, arraysize(rstpProtocolVersions)));

   
   TRACE_DEBUG("  BPDU Type = 0x%02" PRIX8 " (%s)\r\n", bpdu->bpduType,
      rstpGetParamName(bpdu->bpduType, rstpBpduTypes, arraysize(rstpBpduTypes)));

   
   if(length >= RSTP_CONFIG_BPDU_SIZE)
   {
      
      rstpDumpFlags(bpdu->flags);

      
      TRACE_DEBUG("  Root Identifier = %" PRIu16 " / %s\r\n",
         ntohs(bpdu->rootId.priority), macAddrToString(&bpdu->rootId.addr, NULL));

      
      TRACE_DEBUG("  Root Path Cost = %" PRIu32 "\r\n", ntohl(bpdu->rootPathCost));

      
      TRACE_DEBUG("  Bridge Identifier = %" PRIu16 " / %s\r\n",
         ntohs(bpdu->bridgeId.priority), macAddrToString(&bpdu->bridgeId.addr, NULL));

      
      TRACE_DEBUG("  Port Identifier = 0x%04" PRIX16 "\r\n", ntohs(bpdu->portId));

      
      t = ntohs(bpdu->messageAge) * 1000 / 256;
      TRACE_DEBUG("  Message Age = %" PRIu32 ".%03" PRIu32 "\r\n", t / 1000, t % 1000);

      
      t = ntohs(bpdu->maxAge) * 1000 / 256;
      TRACE_DEBUG("  Max Age = %" PRIu32 ".%03" PRIu32 "\r\n", t / 1000, t % 1000);

      
      t = ntohs(bpdu->helloTime) * 1000 / 256;
      TRACE_DEBUG("  Hello Time = %" PRIu32 ".%03" PRIu32 "\r\n", t / 1000, t % 1000);

      
      t = ntohs(bpdu->forwardDelay) * 1000 / 256;
      TRACE_DEBUG("  Forward Delay = %" PRIu32 ".%03" PRIu32 "\r\n", t / 1000, t % 1000);
   }

   
   if(length >= RSTP_RST_BPDU_SIZE)
   {
      
      TRACE_DEBUG("  Version 1 Length = %" PRIu8 "\r\n", bpdu->version1Length);
   }
#endif

   
   return NO_ERROR;
}




void rstpDumpFlags(uint8_t flags)
{
   uint8_t role;

   
   TRACE_DEBUG("  Flags = 0x%02" PRIX8, flags);

   
   if(flags != 0)
   {
      
      TRACE_DEBUG(" (");

      
      while(flags != 0)
      {
         if((flags & RSTP_BPDU_FLAG_TC_ACK) != 0)
         {
            
            TRACE_DEBUG("TcAck");
            
            flags &= ~RSTP_BPDU_FLAG_TC_ACK;
         }
         else if((flags & RSTP_BPDU_FLAG_AGREEMENT) != 0)
         {
            
            TRACE_DEBUG("Agreement");
            
            flags &= ~RSTP_BPDU_FLAG_AGREEMENT;
         }
         else if((flags & RSTP_BPDU_FLAG_FORWARDING) != 0)
         {
            
            TRACE_DEBUG("Forwarding");
            
            flags &= ~RSTP_BPDU_FLAG_FORWARDING;
         }
         else if((flags & RSTP_BPDU_FLAG_LEARNING) != 0)
         {
            
            TRACE_DEBUG("Learning");
            
            flags &= ~RSTP_BPDU_FLAG_LEARNING;
         }
         else if((flags & RSTP_BPDU_FLAG_PORT_ROLE) != 0)
         {
            
            role = flags & RSTP_BPDU_FLAG_PORT_ROLE;

            
            if(role == RSTP_BPDU_FLAG_PORT_ROLE_ALT_BACKUP)
            {
               TRACE_DEBUG("AltBackupRole");
            }
            else if(role == RSTP_BPDU_FLAG_PORT_ROLE_ROOT)
            {
               TRACE_DEBUG("RootRole");
            }
            else if(role == RSTP_BPDU_FLAG_PORT_ROLE_DESIGNATED)
            {
               TRACE_DEBUG("DesignatedRole");
            }

            
            flags &= ~RSTP_BPDU_FLAG_PORT_ROLE;
         }
         else if((flags & RSTP_BPDU_FLAG_PROPOSAL) != 0)
         {
            
            TRACE_DEBUG("Proposal");
            
            flags &= ~RSTP_BPDU_FLAG_PROPOSAL;
         }
         else if((flags & RSTP_BPDU_FLAG_TC) != 0)
         {
            
            TRACE_DEBUG("Tc");
            
            flags &= ~RSTP_BPDU_FLAG_TC;
         }

         
         if(flags != 0)
         {
            TRACE_DEBUG(", ");
         }
      }

      
      TRACE_DEBUG(")");
   }

   
   TRACE_DEBUG("\r\n");
}

#endif
