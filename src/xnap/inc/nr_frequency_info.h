#ifndef NR_FREQUENCY_INFO_H_
#define NR_FREQUENCY_INFO_H_

// #include "nr_frequency_band_item.h"

#include <iostream>
#include <vector>

using NrFrequencyBand = int;
namespace xnap {

struct NrFrequencyInfo {
	int nrARFCN;
    std::vector<NrFrequencyBand> frequencyBandList{};

    friend std::ostream& operator<<(std::ostream& os, const NrFrequencyInfo& g) {
        os << "NrFrequencyInfo{nrARFCN " << g.nrARFCN << "NrFrequencyBand{";
		for (int i = 0; i < g.frequencyBandList.size(); i++){
			os << g.frequencyBandList[i] << ", ";
		}
		os << "}}";
    	return os;
	}
};

} // namespace xnap

#endif // NR_FREQUENCY_INFO_H_