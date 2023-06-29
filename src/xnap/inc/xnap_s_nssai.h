#ifndef XNAP_S_NSSAI_H_
#define XNAP_S_NSSAI_H_

#include <iostream>

namespace xnap {

struct XnapSNssai {
    unsigned int sst; // octet string size 1
    unsigned int sd; // octet string size 3
    bool sdPresence = false;

    friend std::ostream& operator<<(std::ostream& os, const XnapSNssai& p) {
    	os << "XnapSNssai{sst " << p.sst;
        if (p.sdPresence == true){
            os << ", sd " << p.sd;
        }
        os << "}";
    	return os;
	}
};

} // namespace xnap

#endif // XNAP_S_NSSAI_H_