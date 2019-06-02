// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tdatvalue.h 
//
// Создание копии

#ifndef __TDATVALUE_H__
#define __TDATVALUE_H__

class TDatValue;
typedef TDatValue *PTDatValue;

class TDatValue {
  public:
    virtual PTDatValue GetCopy() = 0; // создание копии
	~TDatValue() {}
}; 

#endif //__TDATVALUE_H__
