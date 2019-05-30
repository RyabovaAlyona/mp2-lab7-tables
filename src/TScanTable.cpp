#include "TScanTable.h"

PTDatValue TScanTable :: FindRecord (TKey k) {
	for (int i = 0; i < GetDataCount(); i++) {
		CurrPos = i;
		if (GetKey(CURRENT_POS) == k) return GetValuePTR(CURRENT_POS);
	}
	throw -1;
}
void TScanTable :: InsRecord (TKey k, PTDatValue pVal ) {
	if (IsFull()) throw -1; // ������ ����������, ������� ���������
	for (int i = 0; i < GetDataCount(); i++) {
		CurrPos = i;
		if (GetKey(CURRENT_POS) == k) throw -1; // ������ � ����� ������ ����������
	}
	pRecs[DataCount++] = new TTabRecord(k, pVal);
}
void TScanTable :: DelRecord (TKey k) {
	int flag = 0;
	for (int i = 0; i < GetDataCount(); i++) {
		CurrPos = i;
		if (GetKey(CURRENT_POS) == k) {
			flag++;
			break;
		}
	}
	if (flag == 0) 
		throw -1; // ������ � ����� ������ �� ����������
	if (GetValuePTR(CURRENT_POS) != nullptr) delete pRecs[GetCurrentPos()]->pValue;
	delete pRecs[GetCurrentPos()]; 
	pRecs[GetCurrentPos()] = nullptr;
	// ������� ��������� ������� �� ������ �����
	pRecs[GetCurrentPos()] = pRecs[DataCount - 1];
    pRecs[DataCount - 1] = nullptr;
    DataCount--;
}