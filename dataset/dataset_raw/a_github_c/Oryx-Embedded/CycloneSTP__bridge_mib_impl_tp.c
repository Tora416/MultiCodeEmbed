


#define TRACE_LEVEL SNMP_TRACE_LEVEL


#include "core/net.h"
#include "mibs/mib_common.h"
#include "mibs/bridge_mib_module.h"
#include "mibs/bridge_mib_impl.h"
#include "mibs/bridge_mib_impl_tp.h"
#include "core/crypto.h"
#include "encoding/asn1.h"
#include "encoding/oid.h"
#include "stp/stp.h"
#include "stp/stp_mgmt.h"
#include "rstp/rstp.h"
#include "rstp/rstp_mgmt.h"
#include "debug.h"


#if (BRIDGE_MIB_SUPPORT == ENABLED)




error_t bridgeMibGetDot1dTpLearnedEntryDiscards(const MibObject *object, const uint8_t *oid,
   size_t oidLen, MibVariant *value, size_t *valueLen)
{
   
   
   
   value->counter32 = 0;

   
   return NO_ERROR;
}




error_t bridgeMibSetDot1dTpAgingTime(const MibObject *object, const uint8_t *oid,
   size_t oidLen, const MibVariant *value, size_t valueLen, bool_t commit)
{
#if (BRIDGE_MIB_SET_SUPPORT == ENABLED)
   error_t error;

   
   if(value->integer >= 0)
   {
#if (STP_SUPPORT == ENABLED)
      
      if(bridgeMibBase.stpBridgeContext != NULL)
      {
         
         
         error = stpMgmtSetAgeingTime(bridgeMibBase.stpBridgeContext,
            value->integer, commit);
      }
      else
#endif
#if (RSTP_SUPPORT == ENABLED)
      
      if(bridgeMibBase.rstpBridgeContext != NULL)
      {
         
         
         error = rstpMgmtSetAgeingTime(bridgeMibBase.rstpBridgeContext,
            value->integer, commit);
      }
      else
#endif
      
      {
         
         error = ERROR_WRITE_FAILED;
      }
   }
   else
   {
      
      error = ERROR_WRONG_VALUE;
   }

   
   return error;
#else
   
   return ERROR_WRITE_FAILED;
#endif
}




error_t bridgeMibGetDot1dTpAgingTime(const MibObject *object, const uint8_t *oid,
   size_t oidLen, MibVariant *value, size_t *valueLen)
{
   error_t error;
   uint_t ageingTime;

   
   ageingTime = 0;

#if (STP_SUPPORT == ENABLED)
   
   if(bridgeMibBase.stpBridgeContext != NULL)
   {
      
      
      error = stpMgmtGetAgeingTime(bridgeMibBase.stpBridgeContext,
         &ageingTime);
   }
   else
#endif
#if (RSTP_SUPPORT == ENABLED)
   
   if(bridgeMibBase.rstpBridgeContext != NULL)
   {
      
      
      error = rstpMgmtGetAgeingTime(bridgeMibBase.rstpBridgeContext,
         &ageingTime);
   }
   else
#endif
   
   {
      
      error = ERROR_READ_FAILED;
   }

   
   if(!error)
   {
      
      value->integer = ageingTime;
   }

   
   return error;
}




error_t bridgeMibGetDot1dTpFdbEntry(const MibObject *object, const uint8_t *oid,
   size_t oidLen, MibVariant *value, size_t *valueLen)
{
   error_t error;
   uint_t i;
   size_t n;
   SwitchFdbEntry entry;
   MacAddr dot1dTpFdbAddress;
   NetInterface *interface;

   
   if(bridgeMibBase.interface == NULL)
      return ERROR_READ_FAILED;

   
   interface = bridgeMibBase.interface;

   
   n = object->oidLen;

   
   error = mibDecodeMacAddr(oid, oidLen, &n, &dot1dTpFdbAddress);
   
   if(error)
      return error;

   
   if(n != oidLen)
      return ERROR_INSTANCE_NOT_FOUND;

   
   for(i = 0; !error; i++)
   {
      
      error = interface->switchDriver->getDynamicFdbEntry(interface, i, &entry);

      
      if(error == NO_ERROR)
      {
         
         if(macCompAddr(&entry.macAddr, &dot1dTpFdbAddress))
            break;
      }
      else if(error == ERROR_INVALID_ENTRY)
      {
         
         error = NO_ERROR;
      }
      else
      {
         
      }
   }

   
   if(error)
      return ERROR_INSTANCE_NOT_FOUND;

   
   if(!strcmp(object->name, "dot1dTpFdbAddress"))
   {
      
      if(*valueLen >= sizeof(MacAddr))
      {
         
         
         macCopyAddr(value->octetString, &entry.macAddr);

         
         *valueLen = sizeof(MacAddr);
      }
      else
      {
         
         error = ERROR_BUFFER_OVERFLOW;
      }
   }
   
   else if(!strcmp(object->name, "dot1dTpFdbPort"))
   {
      
      
      
      value->integer = entry.srcPort;
   }
   
   else if(!strcmp(object->name, "dot1dTpFdbStatus"))
   {
      
      value->integer = BRIDGE_MIB_FDB_STATUS_LEARNED;
   }
   
   else
   {
      
      error = ERROR_OBJECT_NOT_FOUND;
   }

   
   return error;
}




error_t bridgeMibGetNextDot1dTpFdbEntry(const MibObject *object, const uint8_t *oid,
   size_t oidLen, uint8_t *nextOid, size_t *nextOidLen)
{
   error_t error;
   uint_t i;
   size_t n;
   MacAddr macAddr;
   SwitchFdbEntry entry;
   NetInterface *interface;

   
   macAddr = MAC_UNSPECIFIED_ADDR;

   
   if(bridgeMibBase.interface == NULL)
      return ERROR_OBJECT_NOT_FOUND;

   
   interface = bridgeMibBase.interface;

   
   if(*nextOidLen < object->oidLen)
      return ERROR_BUFFER_OVERFLOW;

   
   osMemcpy(nextOid, object->oid, object->oidLen);

   
   error = NO_ERROR;

   
   for(i = 0; !error; i++)
   {
      
      error = interface->switchDriver->getDynamicFdbEntry(interface, i, &entry);

      
      if(error == NO_ERROR)
      {
         
         n = object->oidLen;

         
         error = mibEncodeMacAddr(nextOid, *nextOidLen, &n, &entry.macAddr);
         
         if(error)
            return error;

         
         
         if(oidComp(nextOid, n, oid, oidLen) > 0)
         {
            
            
            if(mibCompMacAddr(&macAddr, &MAC_UNSPECIFIED_ADDR) == 0 ||
               mibCompMacAddr(&entry.macAddr, &macAddr) < 0)
            {
               macAddr = entry.macAddr;
            }
         }
      }
      else if(error == ERROR_INVALID_ENTRY)
      {
         
         error = NO_ERROR;
      }
      else
      {
         
      }
   }

   
   
   if(mibCompMacAddr(&macAddr, &MAC_UNSPECIFIED_ADDR) == 0)
      return ERROR_OBJECT_NOT_FOUND;

   
   n = object->oidLen;

   
   error = mibEncodeMacAddr(nextOid, *nextOidLen, &n, &macAddr);
   
   if(error)
      return error;

   
   *nextOidLen = n;
   
   return NO_ERROR;
}




error_t bridgeMibGetDot1dTpPortEntry(const MibObject *object, const uint8_t *oid,
   size_t oidLen, MibVariant *value, size_t *valueLen)
{
   error_t error;
   size_t n;
   uint16_t dot1dTpPort;

   
   n = object->oidLen;

   
   error = mibDecodePort(oid, oidLen, &n, &dot1dTpPort);
   
   if(error)
      return error;

   
   if(n != oidLen)
      return ERROR_INSTANCE_NOT_FOUND;

   
   if(bridgeMibGetPortIndex(dot1dTpPort) == 0)
      return ERROR_INSTANCE_NOT_FOUND;

   
   if(!strcmp(object->name, "dot1dTpPort"))
   {
      
      
      value->integer = dot1dTpPort;
   }
   
   else if(!strcmp(object->name, "dot1dTpPortMaxInfo"))
   {
      
      
      value->integer = ETH_MTU;
   }
   
   else if(!strcmp(object->name, "dot1dTpPortInFrames"))
   {
      
      
      value->counter32 = 0;
   }
   
   else if(!strcmp(object->name, "dot1dTpPortOutFrames"))
   {
      
      
      value->counter32 = 0;
   }
   
   else if(!strcmp(object->name, "dot1dTpPortInDiscards"))
   {
      
      
      value->counter32 = 0;
   }
   
   else
   {
      
      error = ERROR_OBJECT_NOT_FOUND;
   }

   
   return error;
}




error_t bridgeMibGetNextDot1dTpPortEntry(const MibObject *object, const uint8_t *oid,
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
