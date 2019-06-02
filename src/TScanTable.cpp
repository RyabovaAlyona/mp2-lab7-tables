#include "TScanTable.h"

PTDatValue TScanTable :: FindRecord (TKey k) {
	for (int i = 0; i < GetDataCount(); i++) {
		CurrPos = i;
		if (GetKey(CURRENT_POS) == k) {
			Efficiency += i + 1;
			return GetValuePTR(CURRENT_POS);
		}
	}
	throw -1;
}
void TScanTable :: InsRecord (TKey k, PTDatValue pVal ) {
	if (IsFull()) throw -1; // запись невозможна, таблица заполнена
	for (int i = 0; i < GetDataCount(); i++) {
		CurrPos = i;
		if (GetKey(CURRENT_POS) == k) {
			Efficiency += i + 1;
			throw -1; // запись с таким ключом существует
		}
	}
	Efficiency += DataCount;
	pRecs[DataCount++] = new TTabRecord(k, pVal);
}
void TScanTable :: DelRecord (TKey k) {
	if (IsEmpty())
        throw -1;

    for (int i = 0; i < GetDataCount(); i++)
        if (pRecs[i]->GetKey() == k)
        {
            if (pRecs[i]->pValue != nullptr)
                delete pRecs[i]->pValue;
            delete pRecs[i]; pRecs[i] = nullptr;
            pRecs[i] = pRecs[DataCount - 1];
            pRecs[DataCount - 1] = nullptr;
			Efficiency += i+1;
            DataCount--;
            return;
        }
		Efficiency++;
    throw -1;
}