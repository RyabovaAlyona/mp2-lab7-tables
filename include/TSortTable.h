// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tsorttable.h
//
// Реализация упорядоченных таблиц

#ifndef __TSORTTABLE_H
#define __TSORTTABLE_H

#include "TArrayTable.h"
#include "TScanTable.h"

enum TSortMethod {INSERT_SORT, MERGE_SORT, QUIQ_SORT};
class  TSortTable: public TScanTable {
  protected: 
    TSortMethod SortMethod; // метод сортировки
    void SortData (void);   // сортировка данных
    void InsertSort (PTTabRecord *pMem, int DataCount); // метод вставок
    void MergeSort (PTTabRecord *pMem, int DataCount);  // метод слияния
    void MergeSorter (PTTabRecord * &pData,int left,int right);
    void MergeData (PTTabRecord *&pData,int left,int mid,int right);
    void QuiqSort (PTTabRecord *pMem, int DataCount); // быстрая сортировка
    void QuiqSplit (PTTabRecord *&pData, int low, int high);
  public:
    TSortTable(int Size=TabMaxSize): TScanTable(Size){};// конструктор
    TSortTable(const TScanTable &tab); // из просматриваемой таблицы
    TSortTable & operator=(const TScanTable &tab); // присваивание
    TSortMethod GetSortMethod(void);    // получить метод сортировки
    void SetSortMethod (TSortMethod sm);// установить метод сортировки
    // основные методы
    virtual PTDatValue FindRecord (TKey k) ; // найти запись
    virtual void InsRecord (TKey k, PTDatValue pVal ) ; // вставить
    virtual void DelRecord (TKey k) ;        // удалить запись
};

#endif