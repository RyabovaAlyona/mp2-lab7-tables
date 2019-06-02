// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// ttreetable.h
//
// Таблицы со структурой хранения в виде деревьев поиска 

#ifndef __TTREETABLE_H
#define __TTREETABLE_H


#include "TTreeNode.h"
#include "TTable.h"

#include <stack>


class  TTreeTable: public TTable {
  protected: 
    PTTreeNode pRoot; // указатель на корень дерева
    PTTreeNode pRef;// указатель на вершину-результата в FindRecord
    PTTreeNode pCurrent;// указатель на текущую вершину
    int CurrPos;        // номер текущей вершины
    std::stack < PTTreeNode> St;// стек для итератора
    void DeleteTreeTab (PTTreeNode pNode); // удаление
  public:
    TTreeTable(): TTable(){CurrPos=0; pRoot = pCurrent=nullptr; pRef = nullptr;}   
    ~TTreeTable(){DeleteTreeTab (pRoot);} // деструктор

    // информационные методы
    virtual int IsFull ( ) const ; //заполнена?

    //основные методы
    virtual PTDatValue FindRecord (TKey k); // найти запись
    virtual void InsRecord (TKey k, PTDatValue pVal ); // вставить
    virtual void DelRecord (TKey k);       // удалить запись

    // навигация
    virtual TKey GetKey (void) const;
    virtual PTDatValue GetValuePTR (void) const;
    virtual int Reset (void);  // установить на первую запись
    virtual int IsTabEnded (void) const; // таблица завершена?
    virtual int GoNext (void) ;// переход к следующей записи
    //(=1 после применения для последней записи таблицы)
};

#endif