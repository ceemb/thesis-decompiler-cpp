#ifndef NR_MODE_INFO_TDD_H_
#define NR_MODE_INFO_TDD_H_

#include "nr_frequency_info.h"
#include "nr_transmission_bandwidth.h"

#include <iostream>


namespace xnap {

struct NrModeInfoTdd {
	NrFrequencyInfo nrFrequencyInfo;
	NrTransmissionBandwidth nrTransmissonBandwidth;

	friend std::ostream& operator<<(std::ostream& os, const NrModeInfoTdd& g) {
    	os << "NrModeInfoTdd{" << g.nrFrequencyInfo << ", " << g.nrTransmissonBandwidth << "}";
    	return os;
	}
};

} // namespace xnap

#endif // NR_MODE_INFO_TDD_H_