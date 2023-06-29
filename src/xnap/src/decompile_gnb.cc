#include "../inc-function/decompile_gnb.h"
#include "../inc-function/decompile_plmn_id.h"
#include "../inc-function/to_uint.h"

namespace xnap {
namespace decompileGnb {

void DecompileNodeId(const XNAP_GNB_ID_Choice__C& pdu, NodeId& nodeId) { // pdu = pduGnb.gnd_id
 	auto& gnbIdPdu = static_cast<const asncXNAP_gnb_ID&>(pdu);
	
	asnMAXUINT length = 0;
  	asnbyte* value = nullptr;
  	gnbIdPdu.gnb_ID.getBitString(&length, &value);
	// std::cout << "Length = "<< length << std::endl;
  	nodeId = ToUInt::Deserialize64bit(value, length);
}

void DecompileGlobalNgRanNodeIdGnb(const XNAP_GlobalNG_RANNode_ID& pdu, GlobalGnbId& globalGnbId) {
	// std::cout << "Decompiling XNAP_GlobalNG_RANNode_ID__C" << std::endl;
	auto& pduGnb = static_cast<const asncXNAP_GlobalNG_RANNode_ID__gNB&>(*pdu.value); //line 14-15 are stored in pduGnb
	DecompileNodeId(*pduGnb.gnb_id, globalGnbId.nodeId); // store contents of line 15 to local address to variable globalGnbId.nodeId
	decompilePlmn::DecompilePlmnId(pduGnb.plmn_id, globalGnbId.plmnId); // store contents of line 14 to local address to variable globalGnbId.plmnId
}
}
}