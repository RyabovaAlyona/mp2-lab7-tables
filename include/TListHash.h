// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tlisthash.h
//
// Класс для таблиц с вычислимым входом, использующий для разрешения коллизий метод цепочек

#ifndef __TLISTHASH_H
#define __TLISTHASH_H

#include "THashTable.h"
#include "TDatList.h"

#define TabMaxSize 50
class  TListHash : public THashTable {
  protected:
    PTDatList *pList; // память для массива указателей на списки записей 
    int TabSize;      // размер массива указателей
    int CurrList;     // список, в котором выполнялся поиск
  public:
    TListHash(int Size= TabMaxSize); // конструктор
    ~TListHash();
    // информационные методы
    virtual int IsFull ( ) const ; // заполнена?
    // доступ
    virtual TKey GetKey (void) const;
    virtual PTDatValue GetValuePTR (void) const;
    // основные методы
    virtual PTDatValue FindRecord (TKey k); // найти запись
    virtual void InsRecord (TKey k, PTDatValue pVal ); // вставить
    virtual void DelRecord (TKey k);        // удалить запись
    // навигация
    virtual int Reset (void);   // установить на первую запись
    virtual int IsTabEnded (void) const; // таблица завершена?
    virtual int GoNext (void) ; // переход к следующей записи
    //(=1 после применения для последней записи таблицы)
};

#endif