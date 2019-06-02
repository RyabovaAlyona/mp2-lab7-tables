#include "TDatList.h"

	PTDatLink TDatList :: GetLink (PTDatValue pVal, PTDatLink pLink)  
{
	PTDatLink link = new TDatLink(pVal, pLink);
	return link;
}

    void TDatList :: DelLink (PTDatLink pLink)   // удаление звена
	{
		if (pLink != nullptr) {
			if(GetDatValue() != nullptr)
				delete (pLink -> pValue);
			delete pLink;
		}
	}
	TDatList :: TDatList()
	{
		pFirst = nullptr;    // первое звено
		pLast = nullptr;     // последнее звено
		pCurrLink = nullptr; // текущее звено
		pPrevLink = nullptr; // звено перед текущим
		pStop = nullptr;     // значение указателя, означающего конец списка 
		CurrPos = -1;         // номер текущего звена (нумерация от 0)
		ListLen = 0;         // количество звеньев в списке
	}

    // доступ
    PTDatValue TDatList :: GetDatValue (TLinkPos mode) const  // значение
	{
		PTDatLink link;
		switch (mode) {
		case BEGIN: 
			link = pFirst; break;
		case CURRENT: 
			link = pCurrLink; break;
		case END: 
			link = pLast; break;
		default: 
			throw -1;
		}
		return (link==nullptr)?0:link->pValue;
	}
    // навигация
    int TDatList :: SetCurrentPos (int pos)         // установить текущее звено
	{
		if ((pos<0)||(pos>GetListLength()))
			throw -1;
		Reset();
		for (int i=0; i<pos; i++)
			GoNext();
		CurrPos = pos;
		return 0;
	}
    int TDatList :: GetCurrentPos (void) const       // получить номер тек. звена
	{
		return CurrPos;
	}
    int TDatList :: Reset (void) { // установить на начало списка
		pPrevLink = pStop;
		if (IsEmpty()) {
			pCurrLink = pStop;
			CurrPos = -1;
		}
		else {
			pCurrLink = pFirst;
			CurrPos = 0;
		}
		return 0;
	}
	int TDatList :: IsListEnded (void) const { // список завершен ?
		return (pCurrLink == pStop);
	}
    int TDatList :: GoNext (void) {                   // сдвиг вправо текущего звена
                // (=1 после применения GoNext для последнего звена списка)
		if (pCurrLink == pStop)  //уже в конце списка
			return -1;
		else {
			pPrevLink = pCurrLink;
			pCurrLink = pCurrLink -> GetNextDatLink();
			CurrPos++;
			return 0;
		}
	}
    // вставка звеньев
    void TDatList :: InsFirst (PTDatValue pVal) { // перед первым
		PTDatLink link = GetLink(pVal, pFirst);
		if (link == nullptr)
			throw -1;
		pFirst = link;
		if (pLast == nullptr)
			pLast = pFirst;
		Reset();
		ListLen++;

	}
    void TDatList :: InsLast (PTDatValue pVal) { // вставить последним 
		PTDatLink link = GetLink(pVal, pStop);
		if (pLast != nullptr) {
			pPrevLink = pLast;
			pLast -> SetNextLink (link);
		}
		pLast = link;
		pCurrLink = pLast;
		if (ListLen==0) 
			pFirst = pLast;
		Reset();
		ListLen++;
	}
    void TDatList :: InsCurrent (PTDatValue pVal) { // перед текущим 
		if ((pCurrLink == nullptr)||(pPrevLink == nullptr))
			InsFirst (pVal);
		else  {
			PTDatLink link = GetLink(pVal, pCurrLink);
			pPrevLink -> SetNextLink (link);
			pCurrLink = link;
			ListLen++;
		}
		
	}
    // удаление звеньев
    void TDatList :: DelFirst (void) {    // удалить первое звено 
		if (IsEmpty()) 
			throw -1;
		if (pFirst == pLast) 
			pLast = nullptr;
		PTDatLink link = pFirst;
		pFirst = pFirst -> GetNextDatLink();
		DelLink(link);
		Reset();
		ListLen--;
	}
    void TDatList :: DelCurrent (void) {    // удалить текущее звено 
		if (pCurrLink == nullptr) throw -1;
		if (pCurrLink == pFirst) DelFirst();
		else {
			PTDatLink link = pCurrLink;
			pCurrLink = pCurrLink -> GetNextDatLink();
			pPrevLink -> SetNextLink(pCurrLink);
			DelLink(link);
			if (pCurrLink == nullptr) 
				pPrevLink = nullptr;
			ListLen--;
		}
	} 
    void TDatList :: DelList (void) {    // удалить весь список
		while(!IsEmpty())
			DelFirst();
		CurrPos = -1;
		pFirst = pLast = pCurrLink = pPrevLink = pStop;
	}