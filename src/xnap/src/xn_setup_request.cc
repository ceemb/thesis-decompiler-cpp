#include "../inc/xn_setup_request.h"

#include <iostream>
#include <utility>

namespace xnap {

XnSetupRequest::XnSetupRequest(GlobalGnbId globalGnbId, TAISupportList tAISupportIlist, ServedCellInfoList servedCellsList)
	: Message(MessageType::XN_SETUP_REQUEST) 
	, globalGnbId(std::move(globalGnbId))
	, tAISupportIlist(std::move(tAISupportIlist)) 
	, servedCellsList(std::move(servedCellsList)) {}

void XnSetupRequest::Print() const {
	std::cout << "XnSetupRequest{" << globalGnbId << ", \n" << "TAISupportList{";
		for (int i = 0; i< tAISupportIlist.size(); ++i){
			std::cout << tAISupportIlist[i];
		}
		std::cout << "}" << ", \n";
	for (int i = 0; i < servedCellsList.size(); i++)
	{
		std::cout << servedCellsList[i] << ", \n";
	}
}

} // namespace xnap