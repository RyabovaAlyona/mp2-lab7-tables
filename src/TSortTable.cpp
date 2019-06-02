#include "TSortTable.h"


void TSortTable :: SortData (void) {
	switch (SortMethod)
	{
	case INSERT_SORT:
		InsertSort (pRecs, DataCount);
		break;
	case MERGE_SORT:
		MergeSort (pRecs, DataCount);
		break;
	case QUIQ_SORT:
		QuiqSort (pRecs, DataCount);
		break;
	default:
		throw -1;
	}
}
void TSortTable :: InsertSort (PTTabRecord *pMem, int DataCount) {
	if (DataCount == 0)
        return;
	Efficiency += DataCount;
	for (int i = 1; i < GetDataCount(); i++) {
		PTTabRecord tmp = pRecs [i];
		int j = i;
		while ((j > 0) && (tmp -> GetKey() < pRecs[j - 1] -> GetKey ())) {
			pRecs[j] = pRecs [j - 1];
			j--;
			Efficiency++;
		}
		pRecs[j] = tmp;
	}

}
void TSortTable :: MergeSort (PTTabRecord *pMem, int DataCount) {
	if (DataCount == 0)
        return;
    MergeSorter(pMem, 0, DataCount - 1);
}
void TSortTable :: MergeSorter (PTTabRecord * &pData, int left, int right) {
	if (left == right) 
		return;
	int mid = ( left + right ) / 2;
	MergeSorter(pData, left, mid);
	MergeSorter(pData, mid + 1, right);
	MergeData(pData, left, mid, right);
}
void TSortTable :: MergeData (PTTabRecord * &pData, int left, int mid, int right) {
	PTTabRecord* tmp = new PTTabRecord[right - left + 1];
	int i = left, j = mid + 1, n = 0;
	while (i <= mid && j <= right) {
		if (pData[i] -> GetKey() < pData[j] ->GetKey())
			tmp[n++] = pData[i++];
		else
			tmp[n++] = pData[j++];
	}
	if (i > mid)
		while ( j <= right) tmp[n++] = pData [j++];
	if (j > right)
		while ( i <= mid) tmp[n++] = pData [i++];
	n = 0;
	for (i = left; i <= right; i++) 
		pData[i] = tmp[n++];
	delete [] tmp;
}
void TSortTable :: QuiqSort (PTTabRecord *pMem, int DataCount) {
	if (DataCount == 0)
        return;
    QuiqSplit(pMem, 0, DataCount - 1);
}
void TSortTable :: QuiqSplit (PTTabRecord * &pData, int low, int high) { // разбиения массива на три группы:
																// меньшие опорного, равные ему и больше него
	if (low == high)
        return;
	TKey pivot = pRecs[(low + high) / 2]->GetKey(); // опорный элемент
	int i = low, j = high;
	TTabRecord* tmp;
	while (i <= j) {
        while (pRecs[i]->GetKey() < pivot)
            i++;
        while (pRecs[j]->GetKey() > pivot)
            j--;
        if (i <= j)
        {
            tmp = pRecs[i];
            pRecs[i] = pRecs[j];
            pRecs[j] = tmp;
            i++;
            j--;
        }
        QuiqSplit(pData, low, i - 1);
        QuiqSplit(pData, i, high);

	}
}
  
    // public

TSortTable :: TSortTable(const TScanTable &tab) {
	TabSize = tab.GetTabSize();
	DataCount = tab.GetDataCount();
	pRecs = new PTTabRecord[DataCount];
	for (int i = 0; GetDataCount() - 1; i++)
		pRecs[i] = (PTTabRecord)tab.pRecs[i] -> GetCopy();
	if (SortMethod != INSERT_SORT || SortMethod != MERGE_SORT || SortMethod != QUIQ_SORT)
		SortMethod = INSERT_SORT;
	SortData();
	Reset();
}
TSortTable & TSortTable :: operator=(const TScanTable &tab) {
	if (this != &tab) {
		if (pRecs) {
			for (int i = 0; i < DataCount; ++i)
				delete pRecs[i];
			delete[] pRecs;
		}
		TabSize = tab.GetTabSize();
		DataCount = tab.GetDataCount();
		pRecs = new PTTabRecord[TabSize];
		for (int i = 0; i < DataCount; i++)
			pRecs[i] = (PTTabRecord)tab.pRecs[i]->GetCopy();
		SortData();
		CurrPos = 0;
		return *this;
	}
}
TSortMethod TSortTable :: GetSortMethod(void) {
	return SortMethod;
}
void TSortTable :: SetSortMethod (TSortMethod sm) {
	SortMethod = sm;
}

    // основные методы

PTDatValue TSortTable :: FindRecord (TKey k) {
	// бинарный поиск
	Reset();
	if (IsEmpty())
        throw -1;
    if (k < pRecs[0] -> GetKey() || k > pRecs[DataCount - 1] -> GetKey())
    {
        if (k > pRecs[DataCount - 1] -> GetKey())
            CurrPos = DataCount;
        throw -1;
    }
    int left = 0, right = DataCount;
    while ((right - left) > 0)
    {
        Efficiency++;
        int mid = left + (right - left) / 2;
        CurrPos = mid;
        if (pRecs[mid]->GetKey() == k)
        {
            CurrPos = mid;
            return pRecs[mid]->pValue;
        }
        if (pRecs[mid]->GetKey() > k)
            right = mid;
        else left = mid + 1;
    }
    CurrPos = right;

    throw -1;
}
void TSortTable :: InsRecord (TKey k, PTDatValue pVal) {
	if (IsFull()) throw -1;
	try { FindRecord(k); }
	catch (...) {
		for (int i = DataCount; i > CurrPos; --i) {
            pRecs[i] = pRecs[i - 1];
			Efficiency++;
		}
		pRecs[CurrPos] = new TTabRecord(k, pVal);
		DataCount++;
		return;
	}
	throw -1;
}
void TSortTable :: DelRecord (TKey k) {
	if (IsEmpty()) throw -1;
	try { FindRecord(k); }
	catch (...) { throw -1; }
	if (GetValuePTR(CURRENT_POS) != nullptr) delete pRecs[GetCurrentPos()]->pValue;
	delete pRecs[GetCurrentPos()]; 
	pRecs[GetCurrentPos()] = nullptr;
	for (int i = CurrPos; i < DataCount - 1; ++i) {
        pRecs[i] = pRecs[i + 1];
		Efficiency++;
	}
    pRecs[DataCount - 1] = nullptr;
    DataCount--;
	Reset();
}