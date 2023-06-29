#ifndef TAI_SUPPORT_ITEM_H_
#define TAI_SUPPORT_ITEM_H_

#include "broadcast_plmn_in_tai_support.h"

#include <iostream>
#include <cstdint>
#include <limits>
#include <vector>
#include <string>

namespace xnap {

using Tac = uint32_t;
struct TAISupportItem {
	Tac tac;
	std::vector<BroadcastPLMNinTAISupport> broadcastPLMNs{};

	friend std::ostream& operator<<(std::ostream& os, const TAISupportItem& g) {
		os << "TAISupportItem{Tac " << g.tac << ", broadcastPLMNs ";
		for (int i = 0; i < g.broadcastPLMNs.size(); i++)
		{
    		os << g.broadcastPLMNs[i];
		}
		os << "}";
    	return os;
	}
};
using TAISupportList = std::vector<TAISupportItem>;

} // namespace xnap

#endif // TAI_SUPPORT_ITEM_H_