#ifndef PLMN_ID_H_
#define PLMN_ID_H_

#include <iostream>

namespace xnap {

struct PlmnId {
	unsigned int mcc;
	unsigned int mnc;
	unsigned int mncLength;
	friend std::ostream& operator<<(std::ostream& os, const PlmnId& p) {
    	os << "PlmnId{" << p.mcc << ":" << p.mnc << "(" << p.mncLength << ")}";
    	return os;
	}
	bool operator == (const PlmnId& p) 
	{
		return (mcc == p.mcc && mnc == p.mnc);
	}
};

} // namespace xnap

#endif // PLMN_ID_H_