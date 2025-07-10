


#define TRACE_LEVEL STP_TRACE_LEVEL


#include "stp/stp.h"
#include "stp/stp_operation.h"
#include "stp/stp_bpdu.h"
#include "stp/stp_misc.h"
#include "debug.h"


#if (STP_SUPPORT == ENABLED)


const MacAddr STP_BRIDGE_GROUP_ADDR = {{{0x01, 0x80, 0xC2, 0x00, 0x00, 0x00}}};


const StpParamName stpProtocolVersions[] =
{
   {STP_PROTOCOL_VERSION, "STP"}
};


const StpParamName stpBpduTypes[] =
{
   {STP_BPDU_TYPE_CONFIG, "CONFIG"},
   {STP_BPDU_TYPE_TCN,    "TCN"}
};




void stpProcessLlcFrame(NetInterface *interface, EthHeader *ethHeader,
   const uint8_t *data, size_t length, NetRxAncillary *ancillary, void *param)
{
   const LlcHeader *llcHeader;
   const StpBpdu *bpdu;
   StpBridgeContext *context;
   StpBridgePort *port;

   
   context = (StpBridgeContext *) param;

   
   
   if(!macCompAddr(&ethHeader->destAddr, &STP_BRIDGE_GROUP_ADDR))
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

   
   bpdu = (StpBpdu *) (data + sizeof(LlcHeader));

   
   length -= sizeof(LlcHeader);

   
   stpProcessBpdu(port, bpdu, length);
}




error_t stpProcessBpdu(StpBridgePort *port, const StpBpdu *bpdu,
   size_t length)
{
   
   TRACE_INFO("Port %" PRIu8 ": BPDU received (%" PRIuSIZE " bytes)...\r\n",
      port->portIndex, length);

   
   stpDumpBpdu(bpdu, length);

   
   if(length < STP_MIN_BPDU_SIZE)
      return ERROR_INVALID_LENGTH;

   
   if(ntohs(bpdu->protocolId) != STP_PROTOCOL_ID)
      return ERROR_INVALID_LENGTH;

   
   if(bpdu->bpduType == STP_BPDU_TYPE_CONFIG)
   {
      
      if(length < STP_CONFIG_BPDU_SIZE)
         return ERROR_INVALID_LENGTH;

      
      if(ntohs(bpdu->messageAge) >= ntohs(bpdu->maxAge))
         return ERROR_INVALID_PACKET;

      
      stpReceivedConfigBpdu(port, bpdu);
   }
   else if(bpdu->bpduType == STP_BPDU_TYPE_TCN)
   {
      
      stpReceivedTcnBpdu(port, bpdu);
   }
   else
   {
      
      return ERROR_INVALID_TYPE;
   }

   
   return NO_ERROR;
}




error_t stpSendBpdu(StpBridgePort *port, const StpBpdu *bpdu,
   size_t length)
{
   error_t error;
   size_t offset;
   LlcHeader *llcHeader;
   NetBuffer *buffer;
   NetTxAncillary ancillary;
   StpBridgeContext *context;

   
   TRACE_INFO("Port %" PRIu8 ": Sending BPDU (%" PRIuSIZE " bytes)...\r\n",
      port->portIndex, length);

   
   stpDumpBpdu(bpdu, length);

   
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

         
         
         error = ethSendFrame(context->interface, &STP_BRIDGE_GROUP_ADDR,
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




error_t stpDumpBpdu(const StpBpdu *bpdu, size_t length)
{
#if (STP_TRACE_LEVEL >= TRACE_LEVEL_DEBUG)
   uint32_t t;

   
   if(length < STP_MIN_BPDU_SIZE)
      return ERROR_INVALID_LENGTH;

   
   TRACE_DEBUG("  Protocol Identifier = %" PRIu16 "\r\n",
      ntohs(bpdu->protocolId));

   
   TRACE_DEBUG("  Protocol Version Identifier = %" PRIu8 " (%s)\r\n",
      bpdu->protocolVersionId, stpGetParamName(bpdu->protocolVersionId,
      stpProtocolVersions, arraysize(stpProtocolVersions)));

   
   TRACE_DEBUG("  BPDU Type = 0x%02" PRIX8 " (%s)\r\n", bpdu->bpduType,
      stpGetParamName(bpdu->bpduType, stpBpduTypes, arraysize(stpBpduTypes)));

   
   if(length >= STP_CONFIG_BPDU_SIZE)
   {
      
      stpDumpFlags(bpdu->flags);

      
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
#endif

   
   return NO_ERROR;
}




void stpDumpFlags(uint8_t flags)
{
   
   TRACE_DEBUG("  Flags = 0x%02" PRIX8, flags);

   
   if(flags != 0)
   {
      
      TRACE_DEBUG(" (");

      
      while(flags != 0)
      {
         if((flags & STP_BPDU_FLAG_TC_ACK) != 0)
         {
            
            TRACE_DEBUG("TcAck");
            
            flags &= ~STP_BPDU_FLAG_TC_ACK;
         }
         else if((flags & STP_BPDU_FLAG_TC) != 0)
         {
            
            TRACE_DEBUG("Tc");
            
            flags &= ~STP_BPDU_FLAG_TC;
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
