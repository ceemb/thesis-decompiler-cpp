#ifndef XN_SETUP_REQUEST_H_
#define XN_SETUP_REQUEST_H_

#include "message_base.h"
#include "global_gnb_id.h"
#include "tai_support_item.h"
#include "served_cell_info.h"
#include <vector>

namespace xnap {

class XnSetupRequest final : public Message {
public:
	GlobalGnbId globalGnbId;
	TAISupportList tAISupportIlist;
	ServedCellInfoList servedCellsList{};

	XnSetupRequest(GlobalGnbId globalGnbId, TAISupportList tAISupportIlist, ServedCellInfoList servedCellsList);
	virtual ~XnSetupRequest() override = default;

	void Print() const override;

private:
	
};


} // namespace xnap

#endif // XN_SETUP_REQUEST_H_