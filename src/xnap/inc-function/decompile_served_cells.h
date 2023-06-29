#ifndef DECOMPILE_SERVED_CELLS_H_
#define DECOMPILE_SERVED_CELLS_H_

#include "../inc/served_cell_info.h"

namespace xnap {
namespace decompileServedCells {

    void DecompileServedCells(const XNAP_ServedCells_NR& servedCells, ServedCellInfoList& servedCellsList);
    void DecompileCellId(const XNAP_NR_CGI& mCellId, NrCgi& eCellId);
}
}
#endif // DECOMPILE_SERVED_CELLS_H_