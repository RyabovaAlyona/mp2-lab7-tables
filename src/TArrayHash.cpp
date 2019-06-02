#include "TArrayHash.h"


TArrayHash :: TArrayHash(int Size, int Step) {
	if (Size < 0 || Size > TabMaxSize)
		throw -1;
	if (Step < 1 || Step > Size) // Step не может быть больше размера
		throw -1;
	TabSize = Size;
	HashStep = Step;
	pRecs = new PTTabRecord[Size];
    pMark = new TTabRecord("", nullptr);
    for (int i = 0; i < TabSize; ++i)
        pRecs[i] = pMark;
}
TArrayHash :: ~TArrayHash() {
	if (pRecs)
		for (int i = 0; i < TabSize; ++i)
			if (pRecs[i] != pMark) delete pRecs[i];
	delete [] pRecs;
	delete pMark;
}

    // информационные методы

int TArrayHash :: IsFull ( ) const {
	return TabSize == DataCount;
}

    // доступ

TKey TArrayHash :: GetKey (void) const {
	return (CurrPos < 0 || CurrPos >= TabSize) ? "" : pRecs[CurrPos]->GetKey();
}
PTDatValue TArrayHash :: GetValuePTR (void) const {
	return (CurrPos < 0 || CurrPos >= TabSize) ? nullptr : pRecs[CurrPos]->GetValuePTR();
}

    // основные методы

PTDatValue TArrayHash :: FindRecord (TKey k) {
    CurrPos = HashFunc(k) % TabSize;
	FreePos = -1;
	int pos = CurrPos;
    for (int i = 0; i < TabSize; i++)
    {
		Efficiency++;
		if (pRecs[CurrPos] == nullptr)
            throw -1;
        else if (pRecs[CurrPos] == pMark){
            if (FreePos < 0) 
				FreePos = CurrPos;
        } else if (IsEmpty()) 
			throw -1;
        else if (pRecs[CurrPos]-> GetKey() == k)
            return pRecs[CurrPos]->GetValuePTR();
        CurrPos = GetNextPos(CurrPos);
        if (CurrPos == pos)
            break;
    }
	throw -1;
}
void TArrayHash :: InsRecord (TKey k, PTDatValue pVal ) {
	if (IsFull()) 
		throw -1;
	FreePos = -1;   // First free line index
    CurrPos = HashFunc(k) % TabSize;
	Efficiency = 0;
    int originPos = CurrPos;
    while (true)
    {
		Efficiency++;
        if (pRecs[CurrPos] != nullptr && pRecs[CurrPos] != pMark)
        {
            if (pRecs[CurrPos]->GetKey() == k) {
                throw -1;
			}
        }
        else if (pRecs[CurrPos] == pMark)
        {
            if (FreePos < 0) FreePos = CurrPos;
        }
        else if (pRecs[CurrPos] == nullptr)
        {
            if (FreePos < 0)
                pRecs[CurrPos] = new TTabRecord(k, pVal);
            else pRecs[FreePos] = new TTabRecord(k, pVal);
            DataCount++;
            return;
        }
        CurrPos = GetNextPos(CurrPos);
        if (CurrPos == originPos)
        {
            if (FreePos > -1)
            {
                pRecs[FreePos] = new TTabRecord(k, pVal);
                DataCount++;
                return;
            }
            break;
        }
    }
	throw -1;
}
void TArrayHash :: DelRecord (TKey k) {
	if (IsEmpty()) 
		throw -1;
	try { FindRecord(k); }
	catch (...) { throw -1; }
	if (pRecs[CurrPos] ->GetValuePTR())
		delete pRecs[CurrPos] ->pValue;
	pRecs[CurrPos] = pMark;
	DataCount--;
	CurrPos = 0;
}

    // навигация

int TArrayHash :: Reset (void) {
	CurrPos = 0;
	if (!IsTabEnded()) {
		CurrPos = GetNextPos(CurrPos);
		while (CurrPos < TabSize) // поиск занятой строки
			if ((pRecs[CurrPos]!=nullptr) && (pRecs[CurrPos]!=pMark)) break;
	}
	if (pRecs[CurrPos]!=pMark) return CurrPos;
	else return -1;
}
int TArrayHash :: IsTabEnded (void) const {
	return (CurrPos == TabSize);
}
int TArrayHash :: GoNext (void) {
	if (!IsTabEnded()) {
		CurrPos = GetNextPos(CurrPos);
		while (CurrPos < TabSize) // поиск занятой строки
			if ((pRecs[CurrPos]!=nullptr) && (pRecs[CurrPos]!=pMark)) break;
	}
	return IsTabEnded();
}