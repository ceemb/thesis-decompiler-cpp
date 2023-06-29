#ifndef SERVED_CELL_INFO_H_
#define SERVED_CELL_INFO_H_

#include <iostream>
#include <vector>
#include <string>
#include "nr_cgi.h"
#include "plmn_id.h"
#include "nr_mode_info_tdd.h"

namespace xnap {

using Tac = uint32_t;
using ConnectivitySupport = int;
struct ServedCellInfo {

	int nrPci;
	NrCgi cellId;
	Tac tac;
	std::vector<PlmnId> broadcastPLMN{};
	NrModeInfoTdd nrModeInfoTdd;
	std::vector<unsigned char> measurementTimingConfiguration{};
	ConnectivitySupport connectivitySupport;

	friend std::ostream& operator<<(std::ostream& os, const ServedCellInfo& g) {
        os << "ServedCellInfo{NrPci " << g.nrPci << ", " << g.cellId << ", Tac " << g.tac;
		for (int i = 0; i < g.broadcastPLMN.size(); i++){
			os << g.broadcastPLMN[i] << ", ";
		}
		os << g.nrModeInfoTdd;
		for (int j = 0; j < g.measurementTimingConfiguration.size(); j++){
			os << g.measurementTimingConfiguration[j];
		}
	}
};
using ServedCellInfoList = std::vector<ServedCellInfo>;
} // namespace xnap

#endif // SERVED_CELL_INFO_H_