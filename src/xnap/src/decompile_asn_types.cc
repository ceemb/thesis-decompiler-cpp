#include "../inc-function/decompile_asn_types.h"
#include <iostream>

namespace xnap {
namespace decompileAsnTypes {
void DecompileOctetString(const asnOctetString mString, unsigned char* eString){
	asnMAXUINT length = 0;
  	asnbyte* value = nullptr; // pointer, to be able to input arbitrarily sized data rather than just a byte
  	mString.getOctetString(&length, &value);

  	std::copy(value, value + length, eString);	
}
void DecompileOctetVector(const asnOctetString mString, std::vector<unsigned char> eString){
// '&' for length and value to give a pointer to getoctet, so it can write to the actual memory location rather than in a copy of length/value
	asnMAXUINT length = 0;
  	asnbyte* value = nullptr; // pointer, to be able to input arbitrarily sized data rather than just a byte
/pekare så vi kan stoppa in saker med godtycklig längd, inte en byte bara
  	mString.getOctetString(&length, &value);

    eString.emplace_back(*value);
}

Tac DecompileTac(const asnOctetString& asnTac) {
  asnMAXUINT length = 0;
  asnbyte* value = nullptr;
  asnTac.getOctetString(&length, &value);

  Tac tac = value[0] << 16;
  tac |= value[1] << 8;
  tac |= value[2];
  return tac;
}
}
}