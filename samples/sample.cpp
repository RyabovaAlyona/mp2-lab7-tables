#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "TScanTable.h"
#include "TSortTable.h"
#include "TListHash.h"
#include "TBalanceTree.h"
#include "TArrayHash.h"
#include "TTreeTable.h"

using namespace std;

int main () {
	int n = 14;
	vector<string> sur(50);
	TScanTable scan(n);
	TTreeTable ttab;
	TBalanceTree balt;
	TArrayHash arh(n);
	TListHash lhash(n);
	TSortTable sort(n);

	sort.SetSortMethod(INSERT_SORT);

	ifstream in("C:/Users/ComputerInc/Desktop/lab/mp2-lab7-tables/key.txt");
    if (!in.is_open()) return 0;
	for (int i = 0; i < n; i++) {
		string s;
        getline(in, s, '\n');
        cout << s << endl;
        sur[i] = s;
	}

	cout << endl;

	for (int i = 0; i < n; i++) {
		scan.InsRecord(sur[i], nullptr);
		ttab.InsRecord(sur[i], nullptr);
		balt.InsRecord(sur[i], nullptr);
		arh.InsRecord(sur[i], nullptr);
		lhash.InsRecord(sur[i], nullptr);
		sort.InsRecord(sur[i], nullptr);
	}

	cout << "Insert:" << endl;

    cout << "scan_table:          " << scan.GetEfficiency() << endl;
    cout << "sort_table:          " << sort.GetEfficiency() << endl;
    cout << "tree_table:          " << ttab.GetEfficiency() << endl;
    cout << "balance_tree_table:  " << balt.GetEfficiency() << endl;
    cout << "array_hash_table:    " << arh.GetEfficiency() << endl;
    cout << "list_hash_table:     " << lhash.GetEfficiency() << endl;

	scan.ResetEfficiency();
    sort.ResetEfficiency();
    ttab.ResetEfficiency();
    balt.ResetEfficiency();
    arh.ResetEfficiency();
    lhash.ResetEfficiency();

	for (int i = 0; i < n; i++) {
		scan.FindRecord(sur[i]);
		ttab.FindRecord(sur[i]);
		balt.FindRecord(sur[i]);
		arh.FindRecord(sur[i]);
		lhash.FindRecord(sur[i]);
		sort.FindRecord(sur[i]);
	}


	cout << "Find:" << endl;

    cout << "scan_table:          " << scan.GetEfficiency() << endl;
    cout << "sort_table:          " << sort.GetEfficiency() << endl;
    cout << "tree_table:          " << ttab.GetEfficiency() << endl;
    cout << "balance_tree_table:  " << balt.GetEfficiency() << endl;
    cout << "array_hash_table:    " << arh.GetEfficiency() << endl;
    cout << "list_hash_table:     " << lhash.GetEfficiency() << endl;

	scan.ResetEfficiency();
    sort.ResetEfficiency();
    ttab.ResetEfficiency();
    balt.ResetEfficiency();
    arh.ResetEfficiency();
    lhash.ResetEfficiency();


	for (int i = 0; i < n; i++) {
		scan.DelRecord(sur[i]);
		ttab.DelRecord(sur[i]);
		balt.DelRecord(sur[i]);
		arh.DelRecord(sur[i]);
		lhash.DelRecord(sur[i]);
		sort.DelRecord(sur[i]);
	}

	cout << "Delete:" << endl;

    cout << "scan_table:          " << scan.GetEfficiency() << endl;
    cout << "sort_table:          " << sort.GetEfficiency() << endl;
    cout << "tree_table:          " << ttab.GetEfficiency() << endl;
    cout << "balance_tree_table:  " << balt.GetEfficiency() << endl;
    cout << "array_hash_table:    " << arh.GetEfficiency() << endl;
    cout << "list_hash_table:     " << lhash.GetEfficiency() << endl;
	

	for (int i = 0; i < n; i++) {
		scan.InsRecord(sur[i], nullptr);
		ttab.InsRecord(sur[i], nullptr);
		balt.InsRecord(sur[i], nullptr);
		arh.InsRecord(sur[i], nullptr);
		lhash.InsRecord(sur[i], nullptr);
		sort.InsRecord(sur[i], nullptr);
	}
	scan.ResetEfficiency();
    sort.ResetEfficiency();
    ttab.ResetEfficiency();
    balt.ResetEfficiency();
    arh.ResetEfficiency();
    lhash.ResetEfficiency();
	for (int i = n-1; i >= 0; i--) {
		scan.DelRecord(sur[i]);
		ttab.DelRecord(sur[i]);
		balt.DelRecord(sur[i]);
		arh.DelRecord(sur[i]);
		lhash.DelRecord(sur[i]);
		sort.DelRecord(sur[i]);
	}

	cout << "Delete:" << endl;

    cout << "scan_table:          " << scan.GetEfficiency() << endl;
    cout << "sort_table:          " << sort.GetEfficiency() << endl;
    cout << "tree_table:          " << ttab.GetEfficiency() << endl;
    cout << "balance_tree_table:  " << balt.GetEfficiency() << endl;
    cout << "array_hash_table:    " << arh.GetEfficiency() << endl;
    cout << "list_hash_table:     " << lhash.GetEfficiency() << endl;

 	return 0;
}