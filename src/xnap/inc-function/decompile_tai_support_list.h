#ifndef DECOMPILE_TAI_SUPPORT_LIST_H_
#define DECOMPILE_TAI_SUPPORT_LIST_H_

#include "../inc/xnap_s_nssai.h"
#include "../inc/broadcast_plmn_in_tai_support.h"
#include "../inc/tai_support_item.h"

namespace xnap {
namespace decompileTai {
void unloadU32(uint32_t& intValue, const unsigned char* value);
uint32_t getValueAsInt32(const unsigned char* value, unsigned short const bitLength);
void DecompileXnapSNssai(asncXNAP_SliceSupport_Lists* mXnapSNssai, XnapSNssai& eXnapSNssai);
void DecompileBroadcastPLMNs(const asncXNAP_TAISupport_Item__broadcastPLMNss mBroadcastItem, BroadcastPLMNinTAISupport& eBroadcastItem);
void DecompileTaiSupportList(const XNAP_TAISupport_List& mTaiList, TAISupportList& eTaiList);

}
}
#endif // DECOMPILE_TAI_SUPPORT_LIST_H_