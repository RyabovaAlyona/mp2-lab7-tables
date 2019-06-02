#include "TBalanceNode.h"

TDatValue * TBalanceNode :: GetCopy() { 
	if (pValue != nullptr) return new TBalanceNode(Key, pValue->GetCopy(), nullptr, nullptr, Balance);
	else return new TBalanceNode(Key, nullptr, nullptr, nullptr, Balance);
}

int TBalanceNode :: GetBalance(void) const {
	return Balance;
}
void TBalanceNode :: SetBalance(int bal) {
	Balance = bal;
}