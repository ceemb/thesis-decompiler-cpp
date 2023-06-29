#include "../inc-function/decompile_plmn_id.h"
#include "../inc-function/to_uint.h"

namespace xnap {
namespace decompilePlmn {

void DecompilePlmnId(const asnOctetString& pdu, PlmnId& plmnId) {
  	asnMAXUINT length = 0;
  	asnbyte* value = nullptr;
  	pdu.getOctetString(&length, &value);

  	unsigned char octetString[3]; // PlmnId is 3 octets long
  	std::copy(value, value + length, octetString);	

 	unsigned int mcc;
 	unsigned int mnc;
 	unsigned int mncLength;


 	// Convert mcc octet string to uint32_t format
  	mcc = (((octetString[0] & 0x0f) << 8) | (octetString[0] & 0xf0) | (octetString[1] & 0x0f));
    // Convert mnc octet string to U32 format
  	if (((octetString[1] & 0xf0)) == 0xf0) { // fill bit is used, mncLength = 2
    	mnc = (((octetString[2] & 0x0f) << 4) | ((octetString[2] & 0xf0) >> 4));  // | 0x0
    	mncLength = 2;
  	}
  	else {
    	mnc = (((octetString[1] & 0xf0) << 4) | ((octetString[2] & 0x0f) << 4) | ((octetString[2] & 0xf0) >> 4));
    	mncLength = 3;
  	}

  	// Values are BCD-coded as well...
  	plmnId.mcc = ToUInt::BcdToUInt(mcc);
  	plmnId.mnc = ToUInt::BcdToUInt(mnc);
  	plmnId.mncLength = mncLength;

	// std::cout << "PlmnId length " << plmnId.mncLength << ": " << "mcc: " << plmnId.mcc << ", mnc: " << plmnId.mnc << std::endl;
}
}
}