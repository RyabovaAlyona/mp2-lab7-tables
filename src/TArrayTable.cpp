#include "TArrayTable.h"

TArrayTable :: TArrayTable(int Size) { 
	if (Size < 0 || Size > TabMaxSize)
		throw -1;
	TabSize = Size;
	CurrPos = -1;
	pRecs = new PTTabRecord[Size];
	for (int i = 0; i < Size; i++) 
		pRecs[i] = nullptr;
}

    // информационные методы

int TArrayTable :: IsFull() const {
	return DataCount == TabSize;
}
int TArrayTable :: GetTabSize() const {  
	return TabSize;
}

    // доступ

TKey TArrayTable :: GetKey() const {
	return GetKey(CURRENT_POS);
}
PTDatValue TArrayTable :: GetValuePTR() const {
	return GetValuePTR(CURRENT_POS);
}
TKey TArrayTable :: GetKey (TDataPos mode) const {
	switch (mode)
	{
	case FIRST_POS:
		if (pRecs[0] != nullptr) 
			return pRecs[0] -> Key;
		break;
	case CURRENT_POS:
		if (pRecs[CurrPos] != nullptr) 
			return pRecs[CurrPos] -> Key;
		break;
	case LAST_POS:
		if (pRecs[TabSize - 1] != nullptr) 
			return pRecs[TabSize - 1] -> Key;
		break;
	default:
		throw -1;
	}
}
PTDatValue TArrayTable :: GetValuePTR (TDataPos mode) const {
		switch (mode)
	{
	case FIRST_POS:
		if (pRecs[0] != nullptr)
			return pRecs[0] -> pValue;
		break;
	case CURRENT_POS:
		if (pRecs[CurrPos] != nullptr) 
			return pRecs[CurrPos] -> pValue;
		break;
	case LAST_POS:
		if (pRecs[TabSize - 1] != nullptr)
			return pRecs[TabSize - 1] -> pValue;
		break;
	default:
		throw -1;
	}
}

    //навигация

int TArrayTable :: Reset() {
	return CurrPos = 0; 
}
int TArrayTable :: IsTabEnded() const {
	return (CurrPos+1 == TabSize);
}
int TArrayTable :: GoNext() {
	if (IsTabEnded()) return 0;
	else {
		CurrPos++;
		return 1;
	}
}
int TArrayTable :: SetCurrentPos(int pos) {
	if (pos < -1 || pos > TabMaxSize - 1) return 0;
	CurrPos = pos;
	return 1;
}
int TArrayTable :: GetCurrentPos() const {
	return CurrPos;
}