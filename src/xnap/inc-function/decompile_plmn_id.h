#ifndef DECOMPILE_PLMN_ID_H_
#define DECOMPILE_PLMN_ID_H_

#include "../inc/plmn_id.h"

namespace xnap {
namespace decompilePlmn {

void DecompilePlmnId(const asnOctetString& pdu, PlmnId& plmnId);

} // namespace decompilePlmn
} // namespace xnap

#endif // DECOMPILE_PLMN_ID_H_