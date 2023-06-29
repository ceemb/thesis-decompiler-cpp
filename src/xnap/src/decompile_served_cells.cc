#include "../inc-function/decompile_served_cells.h"
#include "../inc-function/decompile_asn_types.h"
#include "../inc-function/decompile_plmn_id.h"
#include "../inc-function/to_uint.h"


#include <iostream>
#include <vector>
#include <typeinfo>
#include <bitset>

namespace xnap {
namespace decompileServedCells {

    void DecompileNrCi(const asnBitString mNrCi, Nci& eNrCi){
	    asnMAXUINT length = 0;
  	    asnbyte* value = nullptr;
        mNrCi.getBitString(&length, &value);
        Nci cellIdentityNr = ToUInt::Deserialize64bit(value, length);
        eNrCi = cellIdentityNr;
    }

    void DecompileCellId(const XNAP_NR_CGI& mCellId, NrCgi& eCellId) { 
	    // std::cout << "Decompiling Cell ID" << std::endl;
        decompilePlmn::DecompilePlmnId(mCellId.plmn_id, eCellId.plmnId);
        DecompileNrCi(mCellId.nr_CI, eCellId.nrCi);
    }

    void DecompileNrModeInfoTddFrequency(XNAP_NRFrequencyInfo* mNrFreqInfo, NrFrequencyInfo& eNrFreqInfo){
        eNrFreqInfo.nrARFCN = mNrFreqInfo->nrARFCN; // nrModeInfo is of type asncXNAP_NRModeInfo__tdd, nrARFCN is of type asnMAXSINT
        // std::cout << "NrMode Info frequency: " << eNrFreqInfo.nrARFCN << std::endl;
        auto* currentBandItem = static_cast<asncXNAP_NRFrequencyBand_Lists*>(mNrFreqInfo->frequencyBand_List.getFirstElement());
        int newFrequencyBandItem;
        for(int i = 0; i < mNrFreqInfo->frequencyBand_List.getCount(); ++i) {
            newFrequencyBandItem = currentBandItem->nr_frequency_band;
            eNrFreqInfo.frequencyBandList.emplace_back(newFrequencyBandItem);
            currentBandItem = static_cast<asncXNAP_NRFrequencyBand_Lists*>(currentBandItem->getNextElement());
            // std::cout << "NrMode Info frequency band: " << eNrFreqInfo.frequencyBandList[i].nrFrequencyBand << std::endl;
        }
    }

    void DecompileNrModeInfoTddTransmission(XNAP_NRTransmissionBandwidth* mNrTransInfo, NrTransmissionBandwidth& eNrTransInfo){
        // Decompile nRSCS
        eNrTransInfo.nRSCS = mNrTransInfo->nRSCS;
        // std::cout << "Transmission nRSCS = " << eNrTransInfo.nRSCS << std::endl;

        // Decompile nRNRB
        eNrTransInfo.nRNRB = mNrTransInfo->nRNRB;
        // std::cout << "Transmission nRNRB = " << eNrTransInfo.nRNRB << std::endl;
    }


    // --------------------------------- start of DecompileServedCells function
    void DecompileServedCells(const XNAP_ServedCells_NR& mServedCells, ServedCellInfoList& eServedCellsList) { // XNAP_ServedCells_NR in the log consists of XnAP-ServedCells-NR-Item (in a list with one entry)
        auto* currentServedCellsItem = static_cast<asncXNAP_ServedCells_NRs*>(mServedCells.value.getFirstElement());

        for(int i = 0; i < mServedCells.value.getCount(); ++i) { // the loop's first item begins on line 33 in the log
            // std::cout << "\n" << "Decompiling Served Cells, loop nr: " << i << std::endl;
            ServedCellInfo newServedCellInfo;
            eServedCellsList.emplace_back(newServedCellInfo);
            eServedCellsList[i].nrPci = currentServedCellsItem->served_cell_info_NR->nrPCI;
            // std::cout << "NR PCI nr: " << eServedCellsList.servedCellsItems[i].servedCellInfo.nrPci << std::endl;

            DecompileCellId(*currentServedCellsItem->served_cell_info_NR->cellID, eServedCellsList[i].cellId);

            eServedCellsList[i].tac = decompileAsnTypes::DecompileTac(currentServedCellsItem->served_cell_info_NR->tac);

            auto* currentBroadcastPLMN = static_cast<asncXNAP_BroadcastPLMNss*>(currentServedCellsItem->served_cell_info_NR->broadcastPLMN.getFirstElement());

            // Loop through list of BroadcastPLMN
            for(int j = 0; j < currentServedCellsItem->served_cell_info_NR->broadcastPLMN.getCount(); ++j) { // the loop's first item begins on line 42 in the log
                PlmnId plmn;
                decompilePlmn::DecompilePlmnId(currentBroadcastPLMN->value, plmn);
                eServedCellsList[i].broadcastPLMN.emplace_back(plmn);
                // emplace attempts to move, otherwise defaults to push 

                currentBroadcastPLMN = static_cast<asncXNAP_BroadcastPLMNss*>(currentBroadcastPLMN->getNextElement());
            }

            if ((currentServedCellsItem->served_cell_info_NR->nrModeInfo->operator==(*(currentServedCellsItem->served_cell_info_NR->nrModeInfo))) ==1) {
                // std::cout << "Choice of type TDD " << std::endl;
                DecompileNrModeInfoTddFrequency(static_cast<asncXNAP_NRModeInfo__tdd*>(currentServedCellsItem->served_cell_info_NR->nrModeInfo)->nrFrequencyInfo, eServedCellsList[i].nrModeInfoTdd.nrFrequencyInfo);
                DecompileNrModeInfoTddTransmission(static_cast<asncXNAP_NRModeInfo__tdd*>(currentServedCellsItem->served_cell_info_NR->nrModeInfo)->nrTransmissonBandwidth, eServedCellsList[i].nrModeInfoTdd.nrTransmissonBandwidth);
            } else {
                // std::cout << "Choice NOT of type TDD " << std::endl;
            }
           
            decompileAsnTypes::DecompileOctetVector(currentServedCellsItem->served_cell_info_NR->measurementTimingConfiguration, eServedCellsList[i].measurementTimingConfiguration);

            eServedCellsList[i].connectivitySupport = currentServedCellsItem->served_cell_info_NR->connectivitySupport->eNDC_Support;
            // std::cout << "eNDC-support: " << eServedCellsList[i].connectivitySupport.eNDCSupport << std::endl;

            currentServedCellsItem = static_cast<asncXNAP_ServedCells_NRs*>(currentServedCellsItem->getNextElement());

        }

    }


}
}