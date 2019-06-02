// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// ttabrecord.h
//
// Класс объектов-значений для записей таблицы

#ifndef __TTABRECORD_H
#define __TTABRECORD_H

#include <string>
#include "TDatValue.h"

class  TTabRecord;
typedef  TTabRecord *PTTabRecord;

typedef std::string TKey;     // тип ключа записи

class TTabRecord : public TDatValue {  
protected:    // поля    
	TKey Key;   // ключ записи
    PTDatValue pValue;   // указатель на значение
public:  // методы
    TTabRecord (TKey k = "", PTDatValue pVal = nullptr); // конструктор 
    void SetKey(TKey k);// установить значение ключа
    TKey GetKey(void) const;  // получить значение ключа
    void SetValuePtr(PTDatValue p);// установить указатель на данные
    PTDatValue GetValuePTR (void) const; // получить указатель на данные
    virtual TDatValue * GetCopy(); // изготовить копию
    TTabRecord & operator = (TTabRecord &tr);// присваивание
    virtual int operator == (const TTabRecord &tr); // сравнение =
    virtual int operator < (const TTabRecord &tr);  // сравнение «<»
    virtual int operator > (const TTabRecord &tr);  // сравнение «>»
//дружественные классы для различных типов таблиц, см. далее
  friend class TArrayTable;
  friend class TScanTable;
  friend class TSortTable;
  friend class TTreeNode;
  friend class TTreeTable;
  friend class TArrayHash;
  friend class TListHash;
};

#endif