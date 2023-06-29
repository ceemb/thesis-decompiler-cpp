#ifndef DECOMPILE_GNB_H_
#define DECOMPILE_GNB_H_

#include "../inc/global_gnb_id.h"

namespace xnap {
namespace decompileGnb {

void DecompileNodeId(const XNAP_GNB_ID_Choice__C& pdu, NodeId& nodeId);
void DecompileGlobalNgRanNodeIdGnb(const XNAP_GlobalNG_RANNode_ID& pdu, GlobalGnbId& globalGnbId);

}
}
#endif // DECOMPILE_GNB_H_