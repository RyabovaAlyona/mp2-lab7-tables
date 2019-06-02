#include <gtest.h>
#include <string>
#include <iostream>

#include "TSortTable.h"
#include "TTabRecord.h"

 TEST(TSortTable, Can_Create_Default_Sort_Table)
{
    ASSERT_NO_THROW(TSortTable());
}

TEST(TSortTable, Cant_Create_Sort_Table_With_Negative_Size) {
	ASSERT_ANY_THROW(TSortTable(-10));
}

TEST(TSortTable, Cant_Create_Sort_Table_With_Size_Large_Max) {
	ASSERT_ANY_THROW(TSortTable(TabMaxSize + 1));
}

TEST(TSortTable, Can_Create_Sort_Table_From_Scan_Table) {
	TScanTable st (1);
	st.InsRecord("iv", nullptr);

	ASSERT_NO_THROW(TSortTable sort(st));
}

TEST(TSortTable, Can_Set_Sort_Method) {
	TSortTable sort;

	ASSERT_NO_THROW(sort.SetSortMethod(INSERT_SORT););
}

TEST(TSortTable, Can_Get_Sort_Method) {
	TSortTable sort;
	TSortMethod sm = MERGE_SORT;
	sort.SetSortMethod(sm);

	EXPECT_EQ(sm, sort.GetSortMethod());
}

TEST(TSortTable, Can_Assign_Sort_Table_From_Scan_Table) {
	TScanTable st (1);
	st.InsRecord("iv", nullptr);
	TSortTable sort;
	sort.SetSortMethod(INSERT_SORT);

	ASSERT_NO_THROW(sort = st);
}

TEST(TSortTable, Create_Sort_Table_From_Scan_Table) {
	TScanTable st (5);
	std::string s[] = {"a", "b", "c", "d", "e"};
	st.InsRecord("c", nullptr);
	st.InsRecord("e", nullptr);
	st.InsRecord("d", nullptr);
	st.InsRecord("b", nullptr);
	st.InsRecord("a", nullptr);
	TSortTable sort;
	sort.SetSortMethod(INSERT_SORT);
	sort = st;
	sort.Reset();
	for (int i = 0; i < 5; i++) {
		EXPECT_TRUE(s[i] == sort.GetKey());
		sort.GoNext();
    }
}

TEST(TSortTable, Correct_Merge_Sort_Of_Table) {
	TScanTable st (5);
	std::string s[] = {"a", "b", "c", "d", "e"};
	st.InsRecord("c", nullptr);
	st.InsRecord("e", nullptr);
	st.InsRecord("d", nullptr);
	st.InsRecord("b", nullptr);
	st.InsRecord("a", nullptr);
	TSortTable sort;
	sort.SetSortMethod(MERGE_SORT);
	sort = st;
	sort.Reset();
	for (int i = 0; i < 5; i++) {
		EXPECT_TRUE(s[i] == sort.GetKey());
		sort.GoNext();
    }
}

TEST(TSortTable, Correct_Quiq_Sort_Of_Table) {
	TScanTable st (5);
	std::string s[] = {"a", "b", "c", "d", "e"};
	st.InsRecord("c", nullptr);
	st.InsRecord("e", nullptr);
	st.InsRecord("d", nullptr);
	st.InsRecord("b", nullptr);
	st.InsRecord("a", nullptr);
	TSortTable sort;
	sort.SetSortMethod(QUIQ_SORT);
	sort = st;
	sort.Reset();
	for (int i = 0; i < 5; i++) {
		EXPECT_TRUE(s[i] == sort.GetKey());
		sort.GoNext();
    }
}

TEST(TSortTable, Can_Insert_Record) {
	TSortTable sort;
	sort.SetSortMethod(INSERT_SORT);
	
	ASSERT_NO_THROW(sort.InsRecord("c", nullptr));
}

TEST(TSortTable, Cant_Insert_Record_When_Key_Exist) {
	TSortTable sort;
	sort.SetSortMethod(INSERT_SORT);
	sort.InsRecord("c", nullptr);
	
	ASSERT_ANY_THROW(sort.InsRecord("c", nullptr));
}

TEST(TSortTable, Can_Find_Record) {
	TSortTable sort;
	sort.InsRecord("a", PTDatValue(1));

	EXPECT_EQ(sort.FindRecord("a"), PTDatValue(1));
}

TEST(TSortTable, Cant_Find_Record_When_It_Isnt_In_Table) {
	TSortTable sort;
	sort.InsRecord("a", PTDatValue(1));

	ASSERT_ANY_THROW(sort.FindRecord("b"));
}

TEST(TSortTable, Can_Delete_Record) {
	TSortTable sort;
	sort.InsRecord("a", nullptr);

	ASSERT_NO_THROW(sort.DelRecord("a"));
}

TEST(TSortTable, Cant_Delete_When_No_Record) {
	TSortTable sort;
	sort.InsRecord("b", nullptr);

	ASSERT_ANY_THROW(sort.DelRecord("a"));
}

TEST(TSortTable, Cant_Delete_When_Table_Is_Empty) {
	TSortTable sort;

	ASSERT_ANY_THROW(sort.DelRecord("a"));
}

