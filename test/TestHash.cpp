#include <gtest.h>
#include <string>
#include <iostream>

#include "TArrayHash.h"
#include "TListHash.h"

TEST(TListHash, Can_Create_Dafault_List_Hash)
{
    ASSERT_NO_THROW(TListHash lh);
}

TEST(TListHash, Cant_Create_List_Hash_With_Negative_Size)
{
    ASSERT_ANY_THROW(TListHash lh(-2));
}

TEST(TListHash, Cant_Create_List_Hash_With_Too_Large_Size)
{
    ASSERT_ANY_THROW(TListHash lh(TabMaxSize+1));
}

TEST(TListHash, Can_Insert_Record_In_List_Hash)
{
	TListHash lh;

    ASSERT_NO_THROW(lh.InsRecord("1", nullptr));
}

TEST(TListHash, Cant_Insert_Record_If_List_Hash_Is_Full)
{
	TListHash lh(3);
	lh.InsRecord("1", nullptr);
	lh.InsRecord("2", nullptr);
	lh.InsRecord("3", nullptr);

    ASSERT_ANY_THROW(lh.InsRecord("4", nullptr));
}

TEST(TListHash, Cant_Insert_Record_If_Key_Exists)
{
	TListHash lh;
	lh.InsRecord("1", nullptr);
	lh.InsRecord("2", nullptr);
	lh.InsRecord("3", nullptr);

    ASSERT_ANY_THROW(lh.InsRecord("3", nullptr));
}

TEST(TListHash, Can_Find_Record_In_List_Hash)
{
	TListHash lh;
	lh.InsRecord("1", nullptr);

    ASSERT_NO_THROW(lh.FindRecord("1"));
}

TEST(TListHash, Cant_Find_Record_If_List_Hash_Is_Empty)
{
	TListHash lh;

    ASSERT_ANY_THROW(lh.FindRecord("4"));
}

TEST(TListHash, Cant_Find_Record_If_This_Key_Not_Exists)
{
	TListHash lh;
	lh.InsRecord("1", nullptr);
	lh.InsRecord("2", nullptr);
	lh.InsRecord("3", nullptr);

    ASSERT_ANY_THROW(lh.FindRecord("4"));
}

TEST(TListHash, Can_Delete_Record_In_List_Hash)
{
	TListHash lh;
	lh.InsRecord("1", nullptr);

	ASSERT_NO_THROW(lh.DelRecord("1"));
}

TEST(TListHash, Cant_Delete_Record_If_List_Hash_Is_Empty)
{
	TListHash lh;

    ASSERT_ANY_THROW(lh.DelRecord("4"));
}

TEST(TListHash, Cant_Delete_Record_If_This_Key_Not_Exists)
{
	TListHash lh;
	lh.InsRecord("1", nullptr);
	lh.InsRecord("2", nullptr);
	lh.InsRecord("3", nullptr);

    ASSERT_ANY_THROW(lh.DelRecord("4"));
}

TEST(TListHash, Delete_Record_Is_Correct)
{
	TListHash lh;
	lh.InsRecord("1", nullptr);
	lh.InsRecord("2", nullptr);
	lh.InsRecord("3", nullptr);

	lh.DelRecord("1");
	lh.DelRecord("2");
	lh.DelRecord("3");

    EXPECT_EQ(1, lh.IsEmpty());
}

// TArrayHash

TEST(TArrayHash, Can_Create_Dafault_Array_Hash)
{
    ASSERT_NO_THROW(TArrayHash ah);
}

TEST(TArrayHash, Cant_Create_Array_Hash_With_Negative_Size)
{
    ASSERT_ANY_THROW(TArrayHash ah(-2));
}

TEST(TArrayHash, Cant_Create_Array_Hash_With_Too_Large_Size)
{
    ASSERT_ANY_THROW(TArrayHash ah(TabMaxSize+1));
}

TEST(TArrayHash, Cant_Create_Array_Hash_With_Step_Less_One)
{
    ASSERT_ANY_THROW(TArrayHash ah(2,0));
}

TEST(TArrayHash, Cant_Create_Array_Hash_With_Too_Large_Step)
{
    ASSERT_ANY_THROW(TArrayHash ah(2,3));
}

TEST(TArrayHash, Can_Find_Record_In_Array_Hash)
{
	TArrayHash ah;
	ah.InsRecord("1", nullptr);

    ASSERT_NO_THROW(ah.FindRecord("1"));
}

TEST(TArrayHash, Cant_Find_Record_If_Array_Hash_Is_Empty)
{
	TArrayHash ah;

    ASSERT_ANY_THROW(ah.FindRecord("1"));
}

TEST(TArrayHash, Cant_Find_Record_If_Key_Not_Exists)
{
	TArrayHash ah;
	ah.InsRecord("1", nullptr);
	ah.InsRecord("2", nullptr);
	ah.InsRecord("3", nullptr);

    ASSERT_ANY_THROW(ah.FindRecord("4"));
}

TEST(TArrayHash, Can_Insert_Record_In_Array_Hash)
{
	TArrayHash ah;

    ASSERT_NO_THROW(ah.InsRecord("1", nullptr));
}

TEST(TArrayHash, Cant_Insert_Record_If_Array_Hash_Is_Full)
{
	TArrayHash ah(3, 1);
	ah.InsRecord("1", nullptr);
	ah.InsRecord("2", nullptr);
	ah.InsRecord("3", nullptr);

    ASSERT_ANY_THROW(ah.InsRecord("4", nullptr));
}

TEST(TArrayHash, Cant_Insert_Record_If_Key_Exists)
{
	TArrayHash ah;
	ah.InsRecord("1", nullptr);
	ah.InsRecord("2", nullptr);
	ah.InsRecord("3", nullptr);

    ASSERT_ANY_THROW(ah.InsRecord("3", nullptr));
}

TEST(TArrayHash, Can_Delete_Record_In_Array_Hash)
{
	TArrayHash ah;
	ah.InsRecord("1", nullptr);

    ASSERT_NO_THROW(ah.DelRecord("1"));
}

TEST(TArrayHash, Cant_Delete_Record_If_Array_Hash_Is_Empty)
{
	TArrayHash ah;

    ASSERT_ANY_THROW(ah.DelRecord("1"));
}

TEST(TArrayHash, Cant_Delete_Record_If_Key_Not_Exists)
{
	TArrayHash ah;
	ah.InsRecord("1", nullptr);
	ah.InsRecord("2", nullptr);
	ah.InsRecord("3", nullptr);

    ASSERT_ANY_THROW(ah.DelRecord("4"));
}

TEST(TArrayHash, Delete_Record_Is_Correct)
{
	TArrayHash ah;
	ah.InsRecord("1", nullptr);
	ah.InsRecord("2", nullptr);
	ah.InsRecord("3", nullptr);

	ah.DelRecord("1");
	ah.DelRecord("2");
	ah.DelRecord("3");

    EXPECT_EQ(1, ah.IsEmpty());
}












