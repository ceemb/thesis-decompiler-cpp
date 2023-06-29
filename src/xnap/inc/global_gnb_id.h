#ifndef GLOBAL_GNB_ID_H_
#define GLOBAL_GNB_ID_H_

#include "plmn_id.h"
#include <vector>
#include <iostream>
#include <cstdint>
#include <limits>

namespace xnap {

using NodeId = std::uint64_t; // cannot fit into 32 bits without adjustments
constexpr NodeId INVALID_NODE_ID = std::numeric_limits<NodeId>::max(); // no constructor; set node id to unreasonable value/sentinel value as default to show that it's not initialized

struct GlobalGnbId {
	NodeId nodeId = INVALID_NODE_ID; 
	PlmnId plmnId;

	friend std::ostream& operator<<(std::ostream& os, const GlobalGnbId& g) {
    	os << "GlobalGnbId{nodeId " << g.nodeId << ", " << g.plmnId << "}";
    	return os;
	}
};

} // namespace xnap

#endif // GLOBAL_GNB_ID_H_