// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tscantable.h
//
// Классом, обеспечивающий реализацию просматриваемых таблиц

#ifndef __TSCANTABLE_H
#define __TSCANTABLE_H

#include "TArrayTable.h"

class  TScanTable: public TArrayTable {
  public:
    TScanTable(int Size=TabMaxSize): TArrayTable(Size){};//конструктор
    // основные методы
    virtual PTDatValue FindRecord (TKey k) ;//найти запись
    virtual void InsRecord (TKey k, PTDatValue pVal ) ;//вставить
    virtual void DelRecord (TKey k) ;//удалить запись
};

#endif