#include "../inc/message_factory.h"

#include "../inc/message_base.h"
#include "../inc/xn_setup_request.h"
#include "../inc/served_cell_info.h"

#include "../inc-function/to_uint.h"
#include "../inc-function/decompile_plmn_id.h"
#include "../inc-function/decompile_gnb.h"
#include "../inc-function/decompile_asn_types.h"
#include "../inc-function/decompile_tai_support_list.h"
#include "../inc-function/decompile_served_cells.h"

#include <cassert>
#include <iostream>

namespace xnap {

namespace {

Message* CreateXnSetupRequest(const XNAP_XnSetupRequest& xnSetupPdu) {
        GlobalGnbId globalGnbId;
		TAISupportList taiSupportList;
		ServedCellInfoList servedCellsList;

        auto* ie = static_cast<asncXNAP_XnSetupRequest__protocolIEss*>(xnSetupPdu.protocolIEs.getFirstElement());
        for(int i = 0; i < xnSetupPdu.protocolIEs.getCount(); ++i) {
            // std::cout << "Decompiling IE " << ie->id << std::endl;
            switch(ie->id) {
                case XNAP_id_GlobalNG_RAN_node_ID__V: { 
                    decompileGnb::DecompileGlobalNgRanNodeIdGnb(static_cast<const XNAP_GlobalNG_RANNode_ID&>(*ie->value), globalGnbId);
                    break; 
                }
				case XNAP_id_TAISupport_list__V: {
					decompileTai::DecompileTaiSupportList(static_cast<const XNAP_TAISupport_List&>(*ie->value), taiSupportList);
					break;
				}
				case XNAP_id_List_of_served_cells_NR__V: {
					decompileServedCells::DecompileServedCells(static_cast<const XNAP_ServedCells_NR&>(*ie->value), servedCellsList);
					break;
				}
				}
            }
			


            ie = static_cast<asncXNAP_XnSetupRequest__protocolIEss*>(ie->getNextElement());
        }
        return new XnSetupRequest(std::move(globalGnbId), std::move(taiSupportList), std::move(servedCellsList));
    }

Message* CreateInitiatingMessage(const asncXNAP_XnAP_PDU__initiatingMessage& initiatingMessage) {
	Message* message = nullptr;

	switch (initiatingMessage.procedureCode) {
        case XNAP_id_xnSetup__V: {
        	message = CreateXnSetupRequest(static_cast<const XNAP_XnSetupRequest&>(*initiatingMessage.value)); // cut off procedure code and criticality (isolating value)
			//std::cout << "Initiating message value = " << initiatingMessage->value << std::endl;
        	break;
        }
    }

	return message;
}

} // namespace 

Message* MessageFactory::Create(const XNAP_XnAP_PDU& xnapPdu) {
	Message* message = nullptr;

	switch (xnapPdu.value->alternative) {
    	case XNAP_initiating_message: {
      		auto& initiatingMessage = static_cast<const asncXNAP_XnAP_PDU__initiatingMessage&>(*xnapPdu.value); 
      		message = CreateInitiatingMessage(initiatingMessage);
			
        	break;
      	}
    }

	return message;
}

} // namespace xnap
