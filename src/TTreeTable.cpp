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

	// �������������� ������

int TTreeTable :: IsFull ( ) const {
	return 0;
}

    //�������� ������

PTDatValue TTreeTable :: FindRecord (TKey k) {
	PTTreeNode ptr = pRoot;
	pRef = nullptr;
	while (ptr) {
		if (ptr ->GetKey() == k) 
			return ptr -> GetValuePTR();
		pRef = ptr;
		if (ptr ->GetKey() > k)
			ptr = ptr -> GetLeft();
		else if (ptr ->GetKey() < k)
			ptr = ptr -> GetRight();
	}
	throw -1;
}

void TTreeTable ::  InsRecord (TKey k, PTDatValue pVal ) {
	try { FindRecord(k); }
	catch (...) {
		if (pRoot == nullptr)  { // ���� ������ ���� ������
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
	PTTreeNode ptr;
	if (pRef == nullptr) ptr = pRoot; // ����� ������� pRoot
	else { // ptr ��������� �� ����, ������� ���������� �������
		if (pRef -> GetKey() > k)
            ptr = pRef -> pLeft;
        else ptr = pRef -> pRight;
	}
	// ������ ��� ��������
	if (ptr -> pRight == nullptr) {
		if (ptr->pLeft == nullptr) { // ��� ����� �����
			if (ptr == pRoot) pRoot = ptr -> pLeft;
			if (pRef && pRef->pRight == ptr) pRef->pRight = nullptr;
			if (pRef && pRef->pLeft == ptr) pRef->pLeft = nullptr;
			if (ptr -> pValue != nullptr)
                delete ptr -> pValue;
            delete ptr;
		}
		else { // ���� ����� ����
			if (ptr == pRoot)
				pRoot = ptr -> pLeft;
			if (pRef && ptr == pRef->pLeft) pRef->pLeft = ptr->pLeft;
            if (pRef && ptr == pRef->pRight) pRef->pRight = ptr->pLeft;
			if (ptr -> pValue != nullptr)
                delete ptr -> pValue;
            delete ptr;

		}
	} else if (ptr->pLeft == nullptr) { // ���� ������ ������ ����
		if (ptr == pRoot) pRoot = ptr -> pRight;
		if (pRef) {
			if (ptr == pRef->pLeft)
                pRef->pLeft = ptr->pRight;
			else pRef->pRight = ptr->pRight;
		}
		ptr -> pRight = nullptr;
		if (ptr -> pValue != nullptr)
               delete ptr -> pValue;
        delete ptr;
	}
	else { // ��� �������
		PTTreeNode v = ptr -> pRight;
		while (v -> pLeft && v -> pLeft -> pLeft) 
			v = v -> pLeft; 
		PTTreeNode n;
		if (v -> pLeft) 
			n = v -> pLeft; // n - ����� ����� ����� ������� ���������, ���� �� ����
		else n = v; //����� ��� ������ ������� ptr
		if (n -> pRight) 
			v -> pLeft = n -> pRight; // ���� � ���� ���� ������ �������
		v -> pLeft = nullptr;
		if (pRef) {
			if (ptr == pRef->pLeft)
					pRef->pLeft = n;
			else pRef->pRight = n;
		}
		if (n != ptr -> pRight) 
			n -> pRight = ptr -> pRight;
		n -> pLeft = ptr -> pLeft;
		if (ptr == pRoot) {
			pRoot = ptr -> pRight;
			pRoot -> pLeft = ptr -> pLeft;
		}
		if (ptr -> pValue != nullptr)
               delete ptr -> pValue;
		delete ptr;
	}
	DataCount--;
}

    // ���������

TKey TTreeTable :: GetKey (void) const {
	return (pCurrent == nullptr) ? TKey("") : pCurrent -> GetKey();
}
PTDatValue TTreeTable :: GetValuePTR (void) const {
	return (pCurrent == nullptr) ? nullptr : pCurrent -> GetValuePTR();
}
int TTreeTable :: Reset (void) {
	PTTreeNode pNode = pCurrent = pRoot;
	while ( !St.empty() ) St.pop(); // ������� �����
	CurrPos = 0;
	while ( pNode != NULL ) { // ������� � ������� ����� �������
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
		PTTreeNode pNode = pCurrent = pCurrent -> GetRight(); // ������� ������
		St.pop();
		while ( pNode != NULL ) { // ������� � ������� ����� �������
			St.push(pNode); 
			pCurrent = pNode; 
			pNode=pNode->GetLeft();
		}
		// ���� ������� ������� ���, �� ���������� �� �����
		if ( (pCurrent==NULL) && !St.empty() ) 
			pCurrent = St.top();
		CurrPos++;
	}
	return IsTabEnded(); 
}

