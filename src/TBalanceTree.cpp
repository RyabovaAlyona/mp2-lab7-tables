#include <math.h>
#include <conio.h>
#include "tbalancetree.h"

#define HeightOK 0 
#define HeightInc 1 

int TBalanceTree :: InsBalanceTree(PTBalanceNode &pNode, TKey k, PTDatValue pVal) {
	int HeighIndex = HeightOK;
	if ( pNode == nullptr ) { // ������� �������
		pNode = new TBalanceNode(k,pVal);
		HeighIndex = HeightInc;
		DataCount++;
	}
	else if ( k < pNode -> GetKey() ) { // ������� � ����� ���������
		if ( InsBalanceTree((PTBalanceNode&)(pNode->pLeft),k,pVal) == HeightInc )
			// ����� ������� ������ ������ ��������� ����������� - ������������
			HeighIndex = LeftTreeBalancing(pNode);
	}
	else if ( k > pNode->GetKey() ) { // ������� � ������ ���������
		if ( InsBalanceTree((PTBalanceNode&)(pNode->pRight),k,pVal) == HeightInc )
			// ����� ������� ������ ������� ��������� ����������� - ������������
			HeighIndex = RightTreeBalancing(pNode);
	}
	else // ���������� ������
		throw -1; 
	return HeighIndex;
}

int TBalanceTree :: LeftTreeBalancing(PTBalanceNode &pNode) {
	int HeighIndex = HeightOK;
	switch ( pNode->GetBalance() ) { // �������� ���������� ������������
    case BalRight: 
		pNode -> SetBalance(BalOk);  // � ��������� ��� ������� ������
        HeighIndex = HeightOK; 
		break;        // �������������� ����������
    case BalOk:    
		pNode->SetBalance(BalLeft);// � ��������� ���� ����������
        HeighIndex = HeightInc; 
		break;       // �������������� ������� �����
    case BalLeft: // � ��������� ��� ������� ����� - ���������� ������������
        PTBalanceNode p1;
        p1 = PTBalanceNode(pNode->pLeft);
        if ( p1 -> GetBalance() == BalLeft ) { // ������ 1 - ����������� LL-�������
			pNode->pLeft = p1->pRight; // 1
            p1->pRight   = pNode;      // 2
            pNode->SetBalance(BalOk);  // 3
            pNode = p1;
        }
        else { // ������ 2 - ���������� LR-�������
            PTBalanceNode p2 = PTBalanceNode (p1->pRight);
            p1->pRight   = p2->pLeft;  // 1
            p2->pLeft    = p1;         // 2
            pNode->pLeft = p2->pRight; // 3
            p2->pRight   = pNode;      // 4
            if ( p2->GetBalance()==BalLeft ) 
				pNode->SetBalance(BalRight);
			else pNode->SetBalance(BalOk); // 5
            if ( p2->GetBalance()==BalRight) 
				p1->SetBalance(BalLeft);
            else p1->SetBalance(BalOk);    // 6
            pNode = p2;
        }
		pNode->SetBalance(BalOk);
		HeighIndex = HeightOK;
		break;
	}
	return HeighIndex;
}
int TBalanceTree :: RightTreeBalancing(PTBalanceNode &pNode) {
	int HeighIndex = HeightOK;
	switch ( pNode->GetBalance() ) { // �������� ���������� ������������
    case BalLeft: 
		pNode -> SetBalance(BalOk);  // � ��������� ��� ������� �����
        HeighIndex = HeightOK; 
		break;        // �������������� ����������
    case BalOk:    
		pNode->SetBalance(BalRight);// � ��������� ���� ����������
        HeighIndex = HeightInc; 
		break;       // �������������� ������� ������
    case BalRight: // � ��������� ��� ������� ������ - ���������� ������������
        PTBalanceNode p1;
        p1 = PTBalanceNode(pNode->pRight);
        if ( p1 -> GetBalance() == BalRight ) { // ������ 1 - ����������� LL-�������
			pNode->pRight = p1->pLeft; // 1
            p1->pLeft   = pNode;      // 2
            pNode->SetBalance(BalOk);  // 3
            pNode = p1;
        }
        else { // ������ 2 - ���������� RR-�������
            PTBalanceNode p2 = PTBalanceNode (p1->pLeft);
            p1->pLeft   = p2->pRight;  // 1
            p2->pRight    = p1;         // 2
            pNode->pRight = p2->pLeft; // 3
            p2->pLeft  = pNode;      // 4
            if ( p2->GetBalance()==BalRight ) 
				pNode->SetBalance(BalLeft);
			else pNode->SetBalance(BalOk); // 5
            if ( p2->GetBalance()==BalLeft) 
				p1->SetBalance(BalRight);
            else p1->SetBalance(BalOk);    // 6
            pNode = p2;
        }
		pNode->SetBalance(BalOk);
		HeighIndex = HeightOK;
		break;
	}
	return HeighIndex;
}

int TBalanceTree :: DeleteBalTree(PTBalanceNode &pNode, TKey k) {
	int HeighIndex = HeightOK;
	if (pNode == nullptr) 
		throw -1;
	else if (pNode && k > pNode -> Key) {
		if (DeleteBalTree((PTBalanceNode&)pNode -> pRight, k))
			HeighIndex = LeftTreeBalancing(pNode);
		} else if (pNode && k < pNode -> Key) {
		if (DeleteBalTree((PTBalanceNode&)pNode -> pLeft, k))
			HeighIndex = RightTreeBalancing(pNode);
		} else { // ����� ����������
		PTTreeNode ptr = pNode;
		if (ptr -> pRight == nullptr) {
			pNode = (PTBalanceNode&)ptr -> pLeft;
			HeighIndex = HeightInc;
		} else if (ptr -> pLeft == nullptr) {
			pNode = (PTBalanceNode&)ptr -> pRight;
			HeighIndex = HeightInc;
		} else {
			 if (DelNode((PTBalanceNode&)ptr->pLeft, (PTBalanceNode&)ptr))
				HeighIndex = RightTreeBalancing(pNode);
			}
		DataCount--;
		}
	}

int TBalanceTree::DelNode(PTBalanceNode& pNode, PTBalanceNode& pParent)
{
    bool HeighIndex = HeightOK;

    if (pNode->pRight != nullptr)
    {
        if (DelNode((PTBalanceNode&)pNode->pRight, pParent))
            HeighIndex = LeftTreeBalancing(pNode);
    }
    else
    {
        delete pParent->pValue;
        pParent->Key = pNode->Key;
        pParent->pValue = pNode->pValue;
        pNode->pValue = nullptr;
        pNode = (PTBalanceNode&)pNode->pLeft;
        HeighIndex = HeightInc;
    }
    return HeighIndex;
}
  
    //�������� ������

void TBalanceTree :: InsRecord (TKey k, PTDatValue pVal ) {
	if (IsFull()) throw -1;
	InsBalanceTree((PTBalanceNode&)pRoot,k,pVal);
}
void TBalanceTree :: DelRecord (TKey k) {
	if (IsEmpty()) 
		throw -1;
	DeleteBalTree((PTBalanceNode&)pRoot,k);

}
