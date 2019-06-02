#include <gtest.h>
#include <string>
#include <iostream>

#include "TScanTable.h"
#include "TTabRecord.h"

 using namespace std;

 TEST(TTabRecord, Can_Create_Default_Record)
{
    ASSERT_NO_THROW(TTabRecord());
}

  TEST(TTabRecord, Can_Create_Record_With_Value)
{
	PTDatValue pVal = nullptr;

    ASSERT_NO_THROW(TTabRecord("iv", pVal));
}

TEST(TTabRecord, Can_Set_Key)
{
    TTabRecord tr;
    
    ASSERT_NO_THROW(tr.SetKey("iv"));
}

TEST(TTabRecord, Can_Get_Key)
{
    TTabRecord tr;
    std::string key("iv");
    tr.SetKey(key);

    EXPECT_EQ(tr.GetKey(), key);
}

TEST(TTabRecord, Can_Set_Value)
{
    TTabRecord tr;
	PTDatValue pVal = nullptr;

	ASSERT_NO_THROW(tr.SetValuePtr(pVal));
}

TEST(TTabRecord, Can_Get_Value)
{
    TTabRecord tr;

    EXPECT_EQ(tr.GetValuePTR(), nullptr);
}

// добавить тесты для getcopy()

TEST(TTabRecord, Correct_Compare_Two_Same_Tab_Record)
{
    TTabRecord tr1 ("iv");
	TTabRecord tr2 ("iv");

    EXPECT_EQ(tr1 == tr2, 1);
}

TEST(TTabRecord, Correct_Compare_Two_Different_Tab_Record)
{
    TTabRecord tr1 ("iv");
	TTabRecord tr2 ("pe");

    EXPECT_EQ(tr1 < tr2, 1);
	EXPECT_EQ(tr2 > tr1, 1);
}

TEST(TScanTable, Can_Create_Default_Scan_Table) {
	ASSERT_NO_THROW(TScanTable());
}

TEST(TScanTable, Cant_Create_Scan_Table_With_Negative_Size) {
	ASSERT_ANY_THROW(TScanTable(-10));
}

TEST(TScanTable, Cant_Create_Scan_Table_With_Size_Large_Max) {
	ASSERT_ANY_THROW(TScanTable(TabMaxSize + 1));
}

TEST(TScanTable, Can_Find_Record) {
	TScanTable st;
	st.InsRecord("iv", PTDatValue(1));

	EXPECT_EQ(st.FindRecord("iv"), PTDatValue(1));
}

TEST(TScanTable, Find_Record_Is_Correct) {
	TScanTable st;
	st.InsRecord("pe", nullptr);

	ASSERT_ANY_THROW(st.FindRecord("iv"));
}

TEST(TScanTable, Can_Insert_Record) {
	TScanTable st;

	ASSERT_NO_THROW(st.InsRecord("iv", nullptr));
}

TEST(TScanTable, Cant_Insert_Record_When_Table_Is_Full) {
	TScanTable st (1);
	st.InsRecord("iv", nullptr);

	ASSERT_ANY_THROW(st.InsRecord("pe", nullptr));
}

TEST(TScanTable, Cant_Insert_Record_When_Key_Exist) {
	TScanTable st;
	st.InsRecord("iv", nullptr);

	ASSERT_ANY_THROW(st.InsRecord("iv", nullptr));
}

TEST(TScanTable, Can_Delete_Record) {
	TScanTable st;
	st.InsRecord("iv", nullptr);

	ASSERT_NO_THROW(st.DelRecord("iv"));
}

TEST(TScanTable, Cant_Delete_When_No_Record) {
	TScanTable st;
	st.InsRecord("pe", nullptr);

	ASSERT_ANY_THROW(st.DelRecord("iv"));
}

TEST(TScanTable, Cant_Delete_When_Table_Is_Empty) {
	TScanTable st;

	ASSERT_ANY_THROW(st.DelRecord("iv"));
}

