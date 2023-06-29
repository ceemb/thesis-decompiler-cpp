#ifndef NR_TRANSMISSION_BANDWIDTH_H_
#define NR_TRANSMISSION_BANDWIDTH_H_

// #include "nr_transmission_bandwidth.h"

#include <iostream>


namespace xnap {

struct NrTransmissionBandwidth {
	int nRSCS;
    int nRNRB;

    friend std::ostream& operator<<(std::ostream& os, const NrTransmissionBandwidth& g) {
    	os << "NrTransmissionBandwidth{nRSCS " << g.nRSCS << ", nRNRB " << g.nRNRB << "}";
    	return os;
	}
};

} // namespace xnap

#endif // NR_TRANSMISSION_BANDWIDTH_H_