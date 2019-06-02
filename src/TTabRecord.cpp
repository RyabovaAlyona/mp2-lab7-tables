#include "TTabRecord.h"

TTabRecord :: TTabRecord (TKey k, PTDatValue pVal) {
	Key = k;
	pValue = pVal;
}
void TTabRecord :: SetKey(TKey k) {
	Key = k;
}
TKey TTabRecord :: GetKey(void) const {
	return Key;
}
void TTabRecord :: SetValuePtr(PTDatValue p) {
	pValue = p;
}
PTDatValue TTabRecord :: GetValuePTR (void) const {
	return pValue;
}
TDatValue * TTabRecord :: GetCopy() {
	return new TTabRecord(Key, pValue);
}
TTabRecord & TTabRecord :: operator = (TTabRecord &tr) {
	if (this != &tr) {
		Key = tr.GetKey();
		if (pValue != nullptr) delete pValue;
		pValue = tr.pValue -> GetCopy();
	}
	return *this; 
}
int TTabRecord :: operator == (const TTabRecord &tr) {
	return Key == tr.GetKey();
}
int TTabRecord :: operator < (const TTabRecord &tr) {
	return Key < tr.GetKey();
}
int TTabRecord :: operator > (const TTabRecord &tr) {
	return Key > tr.GetKey();
}