// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbalancetree.h
//
// Класс для сбалансированных деревьев

#ifndef __TBALANCETREE_H
#define __TBALANCETREE_H

#include "TTreeTable.h"
#include "TBalanceNode.h"

class  TBalanceTree: public TTreeTable  {
    protected: 
int InsBalanceTree(PTBalanceNode &pNode, TKey k, PTDatValue pVal);
int LeftTreeBalancing(PTBalanceNode &pNode); // баланс. левого поддерева
int RightTreeBalancing(PTBalanceNode &pNode);// баланс. правого поддерева
int DeleteBalTree(PTBalanceNode &pNode, TKey k);
int RightDelBalancing(PTBalanceNode& pNode);
int LeftDelBalancing(PTBalanceNode& pNode);
int DelNode(PTBalanceNode& pNode, PTBalanceNode& pParent);
  public:
    TBalanceTree():TTreeTable(){} // конструктор
    //основные методы
    virtual void InsRecord (TKey k, PTDatValue pVal ); // вставить
    virtual void DelRecord (TKey k);                   // удалить
};

#endif