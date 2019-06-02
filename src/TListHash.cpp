#include "TListHash.h"

TListHash :: TListHash(int Size) {
	if (Size <= 0 || Size > TabMaxSize)
		throw -1;
	TabSize = Size;
	CurrList = -1;
	pList = new PTDatList[Size];
    for (int i = 0; i < Size; i++)
        pList[i] = new TDatList();
}

TListHash :: ~ TListHash() {
	if (pList != nullptr) {
		for (int i = 0; i < TabSize; i++)
			delete pList[i];
		delete [] pList;
	}
}

    // информационные методы

int TListHash :: IsFull ( ) const {
	return TabSize == GetDataCount();
}

    // доступ

TKey TListHash :: GetKey (void) const {
	if (CurrList < 0 || IsTabEnded()) return TKey("");
    PTTabRecord tmp = PTTabRecord(pList[CurrList] -> GetDatValue());
	return (tmp == nullptr) ? TKey("") : tmp -> GetKey();
}
PTDatValue TListHash :: GetValuePTR (void) const {
	if (CurrList < 0 || IsTabEnded()) return nullptr;
    PTTabRecord tmp = PTTabRecord (pList[CurrList] -> GetDatValue());
	return (tmp == nullptr) ? nullptr : tmp->GetValuePTR();
}

    // основные методы

PTDatValue TListHash :: FindRecord (TKey k) {
	if (IsEmpty()) 
		throw -1;
    CurrList = HashFunc(k) % TabSize;
    PTDatList tmp = pList[CurrList];  
    for (tmp -> Reset(); !tmp -> IsListEnded(); tmp -> GoNext())
    {
		Efficiency++;
        if (PTTabRecord(tmp -> GetDatValue()) -> GetKey() == k)
            return PTTabRecord(tmp -> GetDatValue()) -> GetValuePTR();
    }
	Efficiency ++;
	throw -1;
}
void TListHash :: InsRecord (TKey k, PTDatValue pVal ) {
	if (IsFull())
		throw -1;
	try { FindRecord(k); }
	catch (...) {
		CurrList = HashFunc(k) % TabSize;
        pList[CurrList] -> InsFirst(new TTabRecord(k, pVal));
        DataCount++;
		Efficiency++;
		return;
	}
	throw -1;
}
void TListHash :: DelRecord (TKey k) {
	if (IsEmpty()) 
		throw -1;
	try { FindRecord(k); }
	catch (...) { throw -1; }
	pList[CurrList] -> DelCurrent();
    DataCount--;
}

    // навигация

int TListHash :: Reset (void) {
	CurrList = 0;
	while (!IsTabEnded() && pList[CurrList]->IsEmpty())
		CurrList++;
	if (IsTabEnded()) 
		return -1;
	else {
        pList[CurrList]->Reset();
        return CurrList;
    }
}
int TListHash :: IsTabEnded (void) const {
	return (CurrList == TabSize);
}
 int TListHash :: GoNext (void) {
	pList[CurrList] -> GoNext();
    if (!(pList[CurrList] -> IsListEnded()))
        return CurrList;
    while (++CurrList && !IsTabEnded())
    {
        if (!(pList[CurrList]->IsEmpty()))
            return pList[CurrList]->Reset();
    }
    return 1;
 }