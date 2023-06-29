#ifndef DECOMPILE_ASN_TYPES_H_
#define DECOMPILE_ASN_TYPES_H_

#include <vector>
#include <cstdint>

namespace xnap {
using Tac = uint32_t;
namespace decompileAsnTypes {
void DecompileOctetString(const asnOctetString mString, unsigned char* eString);
void DecompileOctetVector(const asnOctetString mString, std::vector<unsigned char> eString);
Tac DecompileTac(const asnOctetString& asnTac);
}
}
#endif // DECOMPILE_ASN_TYPES_H_