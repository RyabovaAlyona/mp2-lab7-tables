// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// ttreenode.h
//
// Абстрактный базовый класс объектов-значений для деревьев

#ifndef __TTREENODE_H
#define __TTREENODE_H

#include "TTabRecord.h"

class  TTreeNode;
typedef  TTreeNode *PTTreeNode;

class  TTreeNode: public TTabRecord {
  protected: 
    PTTreeNode pLeft, pRight; // указатели на поддеревья
  public:
    TTreeNode(TKey k = "", PTDatValue pVal = nullptr, PTTreeNode pL = nullptr, 
      PTTreeNode pR = nullptr ): TTabRecord(k, pVal), pLeft(pL), pRight(pR) {};
	PTTreeNode GetLeft(void) const; // указатель на левое поддерево
	PTTreeNode GetRight(void) const; // указатель на правое поддерево
	virtual TDatValue * GetCopy();  // изготовить копию
  friend class TTreeTable;
  friend class TBalanceTree;
};

#endif