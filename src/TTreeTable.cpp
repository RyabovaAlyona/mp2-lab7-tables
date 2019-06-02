#include "TTreeTable.h"
#include <string>


void TTreeTable :: DeleteTreeTab (PTTreeNode pNode) {
	if (pNode == nullptr) return;
	if (pNode ->GetRight() != nullptr)
		DeleteTreeTab(pNode ->GetRight());
	if (pNode -> GetLeft() != nullptr)
		DeleteTreeTab(pNode ->GetLeft());
	if (pNode->pValue != nullptr)
        delete pNode -> pValue;
    delete pNode;
}

	// информационные методы

int TTreeTable :: IsFull ( ) const {
	return 0;
}

    //основные методы

PTDatValue TTreeTable :: FindRecord (TKey k) {
	PTTreeNode ptr = pRoot;
	pRef = nullptr;
	while (ptr) {
		Efficiency++;
		if (ptr ->GetKey() == k) 
			return ptr -> GetValuePTR();
		pRef = ptr;
		if (ptr ->GetKey() > k)
			ptr = ptr -> GetLeft();
		else if (ptr ->GetKey() < k)
			ptr = ptr -> GetRight();
	}
	Efficiency++;
	throw -1;
}

void TTreeTable ::  InsRecord (TKey k, PTDatValue pVal ) {
	try { FindRecord(k); }
	catch (...) {
		if (pRoot == nullptr)  { // если дерево было пустым
            pRoot = new TTreeNode(k, pVal);
			pRoot->pLeft = nullptr;
			pRoot->pRight = nullptr;
		}
		else {
			if (pRef->GetKey() > k) {
                pRef->pLeft = new TTreeNode(k, pVal);
				pRef->pLeft->pLeft = nullptr;
				pRef->pLeft->pRight = nullptr;
			}
            else {
                pRef->pRight = new TTreeNode(k, pVal);
				pRef->pRight->pLeft = nullptr;
				pRef->pRight->pRight = nullptr;
			}
		}
		DataCount++;
		return;
	}
	throw -1;
}

void TTreeTable ::  DelRecord (TKey k) {
	if (IsEmpty()) throw -1;
	try { FindRecord(k); }
	catch (...) { throw -1; }

    PTTreeNode tn = nullptr;

    if (pRef == nullptr) tn = pRoot; 
    else
    {
        if (pRef->GetKey() > k)
            tn = pRef->GetLeft();
        else tn = pRef->GetRight();
    }

    // tn не имеет потомков справа

    if (tn->GetRight() == nullptr)
    {
        if (pRef == nullptr)   // удаление root
        {
            pRoot = tn->pLeft;
            tn->pLeft = nullptr;
            if (tn->GetValuePTR() != nullptr)
                delete tn->pValue;
            delete tn;
        }
        else
        {
            if (tn == pRef->pLeft)
                pRef->pLeft = tn->pLeft;
            else pRef->pRight = tn->pLeft;
            tn->pLeft = nullptr;
            if (tn->GetValuePTR() != nullptr)
                delete tn->pValue;
            delete tn;
        }
    }

    // tn имеет ребенка справа
    else
    {
        PTTreeNode tn2 = tn->pRight;  

        pRef = nullptr;
        while (tn2->pLeft != nullptr)
        {
			Efficiency++;
            pRef = tn2;
            tn2 = tn2->pLeft;
        }
        if (pRef != nullptr)
            pRef->pLeft = tn2->pRight;
        else tn->pRight = tn2->pRight;
        
        if (tn->pValue != nullptr)
            delete tn->pValue;
        tn->pValue = tn2->pValue;
        tn2->pValue = nullptr;
        tn->Key = tn2->Key;
        delete tn2;
    }
    DataCount--;
}

    // навигация

TKey TTreeTable :: GetKey (void) const {
	return (pCurrent == nullptr) ? TKey("") : pCurrent -> GetKey();
}
PTDatValue TTreeTable :: GetValuePTR (void) const {
	return (pCurrent == nullptr) ? nullptr : pCurrent -> GetValuePTR();
}
int TTreeTable :: Reset (void) {
	PTTreeNode pNode = pCurrent = pRoot;
	while ( !St.empty() ) St.pop(); // очистка стека
	CurrPos = 0;
	while ( pNode != NULL ) { // переход к крайней левой вершине
		St.push(pNode); 
		pCurrent = pNode; 
		pNode = pNode -> GetLeft();
	}
	return CurrPos = 0;
}
int TTreeTable :: IsTabEnded (void) const {
	return (CurrPos == DataCount);
}
int TTreeTable :: GoNext (void) {
	if ( !IsTabEnded() && (pCurrent != NULL) ) { 
		PTTreeNode pNode = pCurrent = pCurrent -> GetRight(); // переход вправо
		St.pop();
		while ( pNode != NULL ) { // переход к крайней левой вершине
			St.push(pNode); 
			pCurrent = pNode; 
			pNode=pNode->GetLeft();
		}
		// если правого потомка нет, то извлечение из стека
		if ( (pCurrent==NULL) && !St.empty() ) 
			pCurrent = St.top();
		CurrPos++;
	}
	return IsTabEnded(); 
}

