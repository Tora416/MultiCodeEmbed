


#define TRACE_LEVEL SNMP_TRACE_LEVEL


#include "core/net.h"
#include "mibs/mib_common.h"
#include "mibs/bridge_mib_module.h"
#include "mibs/bridge_mib_impl.h"
#include "mibs/bridge_mib_impl_base.h"
#include "core/crypto.h"
#include "encoding/asn1.h"
#include "encoding/oid.h"
#include "stp/stp.h"
#include "stp/stp_mgmt.h"
#include "rstp/rstp.h"
#include "rstp/rstp_mgmt.h"
#include "debug.h"


#if (BRIDGE_MIB_SUPPORT == ENABLED)




error_t bridgeMibGetDot1dBaseBridgeAddress(const MibObject *object, const uint8_t *oid,
   size_t oidLen, MibVariant *value, size_t *valueLen)
{
   error_t error;
   MacAddr bridgeAddr;

   
   if(*valueLen < sizeof(MacAddr))
      return ERROR_BUFFER_OVERFLOW;

   
   bridgeAddr = MAC_UNSPECIFIED_ADDR;

#if (STP_SUPPORT == ENABLED)
   
   if(bridgeMibBase.stpBridgeContext != NULL)
   {
      
      error = stpMgmtGetBridgeAddr(bridgeMibBase.stpBridgeContext,
         &bridgeAddr);
   }
   else
#endif
#if (RSTP_SUPPORT == ENABLED)
   
   if(bridgeMibBase.rstpBridgeContext != NULL)
   {
      
      error = rstpMgmtGetBridgeAddr(bridgeMibBase.rstpBridgeContext,
         &bridgeAddr);
   }
   else
#endif
   
   {
      
      error = ERROR_READ_FAILED;
   }

   
   if(!error)
   {
      
      macCopyAddr(value->octetString, &bridgeAddr);
      
      *valueLen = sizeof(MacAddr);
   }

   
   return error;
}




error_t bridgeMibGetDot1dBaseNumPorts(const MibObject *object, const uint8_t *oid,
   size_t oidLen, MibVariant *value, size_t *valueLen)
{
   error_t error;
   uint_t numPorts;

   
   numPorts = 0;

#if (STP_SUPPORT == ENABLED)
   
   if(bridgeMibBase.stpBridgeContext != NULL)
   {
      
      error = stpMgmtGetNumPorts(bridgeMibBase.stpBridgeContext, &numPorts);
   }
   else
#endif
#if (RSTP_SUPPORT == ENABLED)
   
   if(bridgeMibBase.rstpBridgeContext != NULL)
   {
      
      error = rstpMgmtGetNumPorts(bridgeMibBase.rstpBridgeContext, &numPorts);
   }
   else
#endif
   
   {
      
      error = ERROR_READ_FAILED;
   }

   
   if(!error)
   {
      
      value->integer = numPorts;
   }

   
   return error;
}




error_t bridgeMibGetDot1dBaseType(const MibObject *object, const uint8_t *oid,
   size_t oidLen, MibVariant *value, size_t *valueLen)
{
   
   value->integer = bridgeMibBase.dot1dBaseType;

   
   return NO_ERROR;
}




error_t bridgeMibGetDot1dBasePortEntry(const MibObject *object, const uint8_t *oid,
   size_t oidLen, MibVariant *value, size_t *valueLen)
{
   error_t error;
   size_t n;
   uint_t portIndex;
   uint16_t dot1dBasePort;

   
   n = object->oidLen;

   
   error = mibDecodePort(oid, oidLen, &n, &dot1dBasePort);
   
   if(error)
      return error;

   
   if(n != oidLen)
      return ERROR_INSTANCE_NOT_FOUND;

   
   portIndex = bridgeMibGetPortIndex(dot1dBasePort);
   
   if(portIndex == 0)
      return ERROR_INSTANCE_NOT_FOUND;

   
   if(!strcmp(object->name, "dot1dBasePort"))
   {
      
      
      value->integer = dot1dBasePort;
   }
   
   else if(!strcmp(object->name, "dot1dBasePortIfIndex"))
   {
      
      
      value->integer = portIndex;
   }
   
   else if(!strcmp(object->name, "dot1dBasePortCircuit"))
   {
      
      if(*valueLen >= sizeof(uint8_t))
      {
         
         
         
         value->oid[0] = 0;

         
         *valueLen = sizeof(uint8_t);
      }
      else
      {
         
         error = ERROR_BUFFER_OVERFLOW;
      }
   }
   
   else if(!strcmp(object->name, "dot1dBasePortDelayExceededDiscards"))
   {
      
      
      
      value->counter32 = 0;
   }
   
   else if(!strcmp(object->name, "dot1dBasePortMtuExceededDiscards"))
   {
      
      
      value->counter32 = 0;
   }
   
   else
   {
      
      error = ERROR_OBJECT_NOT_FOUND;
   }

   
   return error;
}




error_t bridgeMibGetNextDot1dBasePortEntry(const MibObject *object, const uint8_t *oid,
   size_t oidLen, uint8_t *nextOid, size_t *nextOidLen)
{
   error_t error;
   uint_t i;
   size_t n;
   uint_t numPorts;
   uint16_t portNum;
   uint16_t curPortNum;

   
   portNum = 0;

   
   if(*nextOidLen < object->oidLen)
      return ERROR_BUFFER_OVERFLOW;

   
   osMemcpy(nextOid, object->oid, object->oidLen);

   
   numPorts = bridgeMibGetNumPorts();

   
   for(i = 1; i <= numPorts; i++)
   {
      
      curPortNum = bridgeMibGetPortNum(i);

      
      n = object->oidLen;

      
      error = mibEncodeIndex(nextOid, *nextOidLen, &n, curPortNum);
      
      if(error)
         return error;

      
      
      if(oidComp(nextOid, n, oid, oidLen) > 0)
      {
         
         
         if(portNum == 0 || curPortNum < portNum)
         {
            portNum = curPortNum;
         }
      }
   }

   
   
   if(portNum == 0)
      return ERROR_OBJECT_NOT_FOUND;

   
   n = object->oidLen;

   
   error = mibEncodeIndex(nextOid, *nextOidLen, &n, portNum);
   
   if(error)
      return error;

   
   *nextOidLen = n;
   
   return NO_ERROR;
}

#endif
