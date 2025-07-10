


#define TRACE_LEVEL SNMP_TRACE_LEVEL


#include "core/net.h"
#include "mibs/mib_common.h"
#include "mibs/rstp_mib_module.h"
#include "mibs/rstp_mib_impl.h"
#include "core/crypto.h"
#include "encoding/asn1.h"
#include "encoding/oid.h"
#include "debug.h"


#if (RSTP_MIB_SUPPORT == ENABLED)




RstpMibBase rstpMibBase;




const MibObject rstpMibObjects[] =
{
   
   {
      "dot1dStpVersion",
      {43, 6, 1, 2, 1, 17, 2, 16},
      8,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      rstpMibSetDot1dStpVersion,
      rstpMibGetDot1dStpVersion,
      NULL
   },
   
   {
      "dot1dStpTxHoldCount",
      {43, 6, 1, 2, 1, 17, 2, 17},
      8,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      rstpMibSetDot1dStpTxHoldCount,
      rstpMibGetDot1dStpTxHoldCount,
      NULL
   },
   
   {
      "dot1dStpPortProtocolMigration",
      {43, 6, 1, 2, 1, 17, 2, 19, 1, 1},
      10,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      rstpMibSetDot1dStpExtPortEntry,
      rstpMibGetDot1dStpExtPortEntry,
      rstpMibGetNextDot1dStpExtPortEntry
   },
   
   {
      "dot1dStpPortAdminEdgePort",
      {43, 6, 1, 2, 1, 17, 2, 19, 1, 2},
      10,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      rstpMibSetDot1dStpExtPortEntry,
      rstpMibGetDot1dStpExtPortEntry,
      rstpMibGetNextDot1dStpExtPortEntry
   },
   
   {
      "dot1dStpPortOperEdgePort",
      {43, 6, 1, 2, 1, 17, 2, 19, 1, 3},
      10,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,
      MIB_ACCESS_READ_ONLY,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      rstpMibGetDot1dStpExtPortEntry,
      rstpMibGetNextDot1dStpExtPortEntry
   },
   
   {
      "dot1dStpPortAdminPointToPoint",
      {43, 6, 1, 2, 1, 17, 2, 19, 1, 4},
      10,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      rstpMibSetDot1dStpExtPortEntry,
      rstpMibGetDot1dStpExtPortEntry,
      rstpMibGetNextDot1dStpExtPortEntry
   },
   
   {
      "dot1dStpPortOperPointToPoint",
      {43, 6, 1, 2, 1, 17, 2, 19, 1, 5},
      10,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,
      MIB_ACCESS_READ_ONLY,
      NULL,
      NULL,
      sizeof(int32_t),
      NULL,
      rstpMibGetDot1dStpExtPortEntry,
      rstpMibGetNextDot1dStpExtPortEntry
   },
   
   {
      "dot1dStpPortAdminPathCost",
      {43, 6, 1, 2, 1, 17, 2, 19, 1, 6},
      10,
      ASN1_CLASS_UNIVERSAL,
      ASN1_TYPE_INTEGER,
      MIB_ACCESS_READ_WRITE,
      NULL,
      NULL,
      sizeof(int32_t),
      rstpMibSetDot1dStpExtPortEntry,
      rstpMibGetDot1dStpExtPortEntry,
      rstpMibGetNextDot1dStpExtPortEntry
   }
};




const MibModule rstpMibModule =
{
   "RSTP-MIB",
   {43, 6, 1, 2, 1, 129, 6},
   7,
   rstpMibObjects,
   arraysize(rstpMibObjects),
   rstpMibInit,
   NULL,
   NULL,
   NULL,
   NULL
};

#endif
