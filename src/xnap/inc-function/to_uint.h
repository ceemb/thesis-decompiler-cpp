#ifndef TO_UINT_H_
#define TO_UINT_H_

#include <cassert>
#include <iostream>

namespace xnap {
namespace ToUInt {

unsigned int BcdToUInt(unsigned int from);
std::uint64_t Deserialize64bit(const unsigned char source[8], unsigned int bitLength);
} // namespace ToUInt 
} // namespace xnap

#endif // TO_UINT_H_