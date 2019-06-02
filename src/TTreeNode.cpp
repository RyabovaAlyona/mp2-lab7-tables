#include "TTreeNode.h"

PTTreeNode TTreeNode :: GetLeft(void) const {
	return pLeft;
}

PTTreeNode TTreeNode :: GetRight(void) const {
	return pRight;
}

TDatValue * TTreeNode :: GetCopy() { 
	return new TTreeNode(Key, pValue, NULL, NULL);
}
