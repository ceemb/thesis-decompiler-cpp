#include "../inc-function/to_uint.h"

namespace xnap {
namespace ToUInt {

unsigned int BcdToUInt(unsigned int from) {
  // Initialise output number and factor
  unsigned int number = 0;
  unsigned int factor = 1;

  while (from > 0) {
    number += ((from & 0xf) * factor);
    from = (from >> 4);
    factor *= 10;
  }
  return number;
}

std::uint64_t Deserialize64bit(const unsigned char source[8], unsigned int bitLength) {
  unsigned char tmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  unsigned int nrOfBytes = (bitLength + 7) / 8;

  for (unsigned int i = 0; i < nrOfBytes; ++i) {
    tmp[i] = source[i];
  }

  uint64_t value = static_cast<uint64_t>(tmp[0]) << 56;
  value |= static_cast<uint64_t>(tmp[1]) << 48;
  value |= static_cast<uint64_t>(tmp[2]) << 40;
  value |= static_cast<uint64_t>(tmp[3]) << 32;
  value |= static_cast<uint64_t>(tmp[4]) << 24;
  value |= static_cast<uint64_t>(tmp[5]) << 16;
  value |= static_cast<uint64_t>(tmp[6]) << 8;
  value |= static_cast<uint64_t>(tmp[7]);

  return value >> (64 - bitLength);
}
}
}