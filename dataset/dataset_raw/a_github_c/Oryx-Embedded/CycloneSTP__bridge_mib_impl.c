


#define TRACE_LEVEL SNMP_TRACE_LEVEL


#include "core/net.h"
#include "mibs/mib_common.h"
#include "mibs/bridge_mib_module.h"
#include "mibs/bridge_mib_impl.h"
#include "core/crypto.h"
#include "encoding/asn1.h"
#include "encoding/oid.h"
#include "stp/stp.h"
#include "stp/stp_mgmt.h"
#include "stp/stp_misc.h"
#include "rstp/rstp.h"
#include "rstp/rstp_mgmt.h"
#include "rstp/rstp_misc.h"
#include "debug.h"


#if (BRIDGE_MIB_SUPPORT == ENABLED)




error_t bridgeMibInit(void)
{
   
   TRACE_INFO("Initializing Bridge MIB base...\r\n");

   
   memset(&bridgeMibBase, 0, sizeof(bridgeMibBase));

   
   bridgeMibBase.dot1dBaseType = BRIDGE_MIB_BASE_TYPE_TRANSPARENT_ONLY;
   
   bridgeMibBase.dot1dStpProtocolSpecification = BRIDGE_MIB_PROTOCOL_SPEC_IEEE802_1D;

   
   return NO_ERROR;
}




error_t bridgeMibSetStpBridgeContext(StpBridgeContext *context)
{
#if (STP_SUPPORT == ENABLED)
   
   if(context != NULL)
   {
      bridgeMibBase.stpBridgeContext = context;
      bridgeMibBase.interface = context->interface;
   }
   else
   {
      bridgeMibBase.stpBridgeContext = NULL;
      bridgeMibBase.interface = NULL;
   }

   
   return NO_ERROR;
#else
   
   return ERROR_NOT_IMPLEMENTED;
#endif
}




error_t bridgeMibSetRstpBridgeContext(RstpBridgeContext *context)
{
#if (RSTP_SUPPORT == ENABLED)
   
   if(context != NULL)
   {
      bridgeMibBase.rstpBridgeContext = context;
      bridgeMibBase.interface = context->interface;
   }
   else
   {
      bridgeMibBase.rstpBridgeContext = NULL;
      bridgeMibBase.interface = NULL;
   }

   
   return NO_ERROR;
#else
   
   return ERROR_NOT_IMPLEMENTED;
#endif
}




uint_t bridgeMibGetNumPorts(void)
{
   uint_t numPorts;

   
   numPorts = 0;

#if (STP_SUPPORT == ENABLED)
   
   if(bridgeMibBase.stpBridgeContext != NULL)
   {
      numPorts = bridgeMibBase.stpBridgeContext->numPorts;
   }
   else
#endif
#if (RSTP_SUPPORT == ENABLED)
   
   if(bridgeMibBase.rstpBridgeContext != NULL)
   {
      numPorts = bridgeMibBase.rstpBridgeContext->numPorts;
   }
   else
#endif
   
   {
      
   }

   
   return numPorts;
}




uint_t bridgeMibGetPortIndex(uint16_t portNum)
{
   uint_t portIndex;

   
   portIndex = 0;

#if (STP_SUPPORT == ENABLED)
   
   if(bridgeMibBase.stpBridgeContext != NULL)
   {
      StpBridgePort *port;

      
      port = stpGetBridgePort(bridgeMibBase.stpBridgeContext, portNum);

      
      if(port != NULL)
      {
         
         portIndex = port->portIndex;
      }
   }
   else
#endif
#if (RSTP_SUPPORT == ENABLED)
   
   if(bridgeMibBase.rstpBridgeContext != NULL)
   {
      RstpBridgePort *port;

      
      port = rstpGetBridgePort(bridgeMibBase.rstpBridgeContext, portNum);

      
      if(port != NULL)
      {
         
         portIndex = port->portIndex;
      }
   }
   else
#endif
   
   {
      
   }

   
   return portIndex;
}




uint16_t bridgeMibGetPortNum(uint16_t portIndex)
{
   uint_t portNum;

   
   portNum = 0;

#if (STP_SUPPORT == ENABLED)
   
   if(bridgeMibBase.stpBridgeContext != NULL)
   {
      
      if(portIndex >= 1 && portIndex <= bridgeMibBase.stpBridgeContext->numPorts)
      {
         StpBridgePort *port;

         
         port = &bridgeMibBase.stpBridgeContext->ports[portIndex - 1];
         
         portNum = port->portId & STP_PORT_NUM_MASK;
      }
   }
   else
#endif
#if (RSTP_SUPPORT == ENABLED)
   
   if(bridgeMibBase.rstpBridgeContext != NULL)
   {
      
      if(portIndex >= 1 && portIndex <= bridgeMibBase.rstpBridgeContext->numPorts)
      {
         RstpBridgePort *port;

         
         port = &bridgeMibBase.rstpBridgeContext->ports[portIndex - 1];
         
         portNum = port->portId & RSTP_PORT_NUM_MASK;
      }
   }
   else
#endif
   
   {
      
   }

   
   return portNum;
}

#endif
