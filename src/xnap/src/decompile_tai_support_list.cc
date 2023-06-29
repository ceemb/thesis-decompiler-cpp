#include "../inc-function/decompile_tai_support_list.h"
#include "../inc-function/decompile_plmn_id.h"
#include "../inc-function/decompile_asn_types.h"

#include <iostream>


namespace xnap {
namespace decompileTai {

void unloadU32(uint32_t& intValue, const unsigned char* value) {
	intValue = value[0] << 24;
	intValue |= value[1] << 16;
	intValue |= value[2] << 8;
	intValue |= value[3];
}

uint32_t getValueAsInt32(const unsigned char* value, unsigned short const bitLength) {
  uint32_t result = 0;
  unsigned char tmp[4] = {0, 0, 0, 0};
  if (bitLength <= 32) {
    uint32_t nrOfBytes = (bitLength + 7) / 8;
    for (uint32_t i = 0; i < nrOfBytes && i < 4; i++) {
      tmp[i] = value[i];
    }
    unloadU32(result, tmp);
    return result >> (32 - bitLength);
  }
  else {
    return result;
  }
}

void DecompileXnapSNssai(asncXNAP_SliceSupport_Lists* mXnapSNssai, XnapSNssai& eXnapSNssai){
	asnMAXUINT sstLength = 0;
  	asnbyte* sstValue = nullptr;
  	mXnapSNssai->sst.getOctetString(&sstLength, &sstValue);
	uint32_t sst = getValueAsInt32(sstValue, sstLength * 8);
	eXnapSNssai.sst = sst;
	// std::cout << "eXnapSNssai.sst: " << eXnapSNssai.sst << std::endl;

	if(mXnapSNssai->optional.getPresence(asn_XNAP_sd)){
		asnMAXUINT sdLength = 0;
		asnbyte* sdValue = nullptr;
		mXnapSNssai->sd.getOctetString(&sdLength, &sdValue);
		uint32_t sd = getValueAsInt32(sdValue, sdLength * 8);
		eXnapSNssai.sd = sd;
		// std::cout << "eXnapSNssai.sd: " << eXnapSNssai.sd << std::endl;
		eXnapSNssai.sdPresence = true;
	} // end if
}


void DecompileBroadcastPLMNs(const asncXNAP_TAISupport_Item__broadcastPLMNss mBroadcastItem, BroadcastPLMNinTAISupport& eBroadcastItem) {
	// std::cout << "Entered decompileing brodecast " << std::endl;
	decompilePlmn::DecompilePlmnId(mBroadcastItem.plmn_id, eBroadcastItem.plmnId);

	auto* currentXnapSNssai = static_cast<asncXNAP_SliceSupport_Lists*>(mBroadcastItem.tAISliceSupport_List.getFirstElement());
	int count = mBroadcastItem.tAISliceSupport_List.getCount();

	for(int i = 0; i < count; ++i) {
		// std::cout << "\nEntetred loop, i =" << i << std::endl;
		XnapSNssai newTaiSliceSupportList;
		DecompileXnapSNssai(currentXnapSNssai, newTaiSliceSupportList);
		eBroadcastItem.taiSliceSupportList.emplace_back(newTaiSliceSupportList);
		currentXnapSNssai = static_cast<asncXNAP_SliceSupport_Lists*>(currentXnapSNssai->getNextElement());
	}
}


void DecompileTaiSupportList(const XNAP_TAISupport_List& mTaiList, TAISupportList& eTaiList) {
	// std::cout << "Decompileing our taisupport list\n" << std::endl;
	// tailist has tai-item, which has tac, rad 139662 in xnap_type.h

	auto* currentSupportItem = static_cast<asncXNAP_TAISupport_Lists*>(mTaiList.value.getFirstElement()); 
	int count = mTaiList.value.getCount();

	int countPLMN;
	for(int i = 0; i < count; ++i) {
		// std::cout << "Decompiling Support Item " << i << std::endl;
		TAISupportItem newTAISupportItem;
		newTAISupportItem.tac = decompileAsnTypes::DecompileTac(currentSupportItem->tac);
		eTaiList.emplace_back(newTAISupportItem);
		
		// ----Loop for decompiling broadcastPLMNs---
		countPLMN = currentSupportItem->broadcastPLMNs.getCount();
		auto* currentBroadcastItem = static_cast<asncXNAP_TAISupport_Item__broadcastPLMNss*>(currentSupportItem->broadcastPLMNs.getFirstElement());
		for(int j = 0; j < countPLMN; ++j) {
			// std::cout << "Inner loop " << j << std::endl;
			BroadcastPLMNinTAISupport newBroadcastPLMNs;
			DecompileBroadcastPLMNs(*currentBroadcastItem, newBroadcastPLMNs); // decompile each element in broadcastPLMNs-list
			eTaiList[i].broadcastPLMNs.emplace_back(newBroadcastPLMNs);
			currentBroadcastItem = static_cast<asncXNAP_TAISupport_Item__broadcastPLMNss*>(currentBroadcastItem->getNextElement());
	
		}
		currentSupportItem = static_cast<asncXNAP_TAISupport_Lists*>(currentSupportItem->getNextElement());
	}	
	// std::cout << "Finished decompiling taisupport list" << std::endl;
}
}
}
