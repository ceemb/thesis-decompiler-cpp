#ifndef NR_CGI_H_
#define NR_CGI_H_

#include <iostream>

#include "plmn_id.h"
// #include "nr_ci.h"


namespace xnap {
using Nci = uint64_t;
struct NrCgi {
	PlmnId plmnId;
    Nci nrCi;

    friend std::ostream& operator<<(std::ostream& os, const NrCgi& g) {
    	os << "NrCgi{" << g.plmnId << ", Nci: " << g.nrCi << "}";
    	return os;
	}
};

} // namespace xnap

#endif // NR_CGI_H_