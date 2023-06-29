#ifndef BROADCAST_PLMN_IN_TAI_SUPPORT_H_
#define BROADCAST_PLMN_IN_TAI_SUPPORT_H_

#include "plmn_id.h"
#include "xnap_s_nssai.h"

#include <iostream>
#include <vector>

namespace xnap {

struct BroadcastPLMNinTAISupport {
	PlmnId plmnId;
	std::vector<XnapSNssai> taiSliceSupportList{};

	friend std::ostream& operator<<(std::ostream& os, const BroadcastPLMNinTAISupport& g) {
		os << "BroadcastPLMNinTAISupport{" << g.plmnId;
		for (int i = 0; i < g.taiSliceSupportList.size(); ++i) {
    		os << g.taiSliceSupportList[i];
		}
		os << "}";
    	return os;
	}

};

} // namespace xnap

#endif // BROADCAST_PLMN_IN_TAI_SUPPORT_H_