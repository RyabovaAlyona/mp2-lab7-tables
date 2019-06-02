// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// thashtable.h
//
// Базовый класс для таблиц с вычислимым входом

#ifndef __THASHTABLE_H
#define __THASHTABLE_H

#include "TTable.h"

class  THashTable : public TTable {
  protected:
    virtual unsigned long HashFunc(const TKey key); // hash-функция
  public:
    THashTable() : TTable() {} //конструктор
};

#endif