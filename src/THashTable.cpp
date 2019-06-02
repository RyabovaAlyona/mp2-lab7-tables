#include "THashTable.h"

unsigned long THashTable :: HashFunc(const TKey key) {
	unsigned long hash = 0;
	int len = key.length();
	for(int i = 0; i < len; i++)
		hash = (hash << 3) + key[i];
	return hash;
}