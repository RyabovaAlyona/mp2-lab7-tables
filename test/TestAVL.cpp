#include <gtest.h>
#include <string>
#include <iostream>

#include "TBalanceNode.h"
#include "TBalanceTree.h"

TEST(TBalanceNode, Can_Create_Dafault_Balance_Tree_Node)
{
    ASSERT_NO_THROW(TBalanceNode bn);
}

TEST(TBalanceNode, Can_Set_Balance)
{
    TBalanceNode bn;

    ASSERT_NO_THROW(bn.SetBalance(1));
}

TEST(TBalanceNode, Can_Get_Balance)
{
    TBalanceNode bn;
	bn.SetBalance(1);

    EXPECT_EQ(bn.GetBalance(), 1);
}

TEST(TBalanceTree, Can_Create_Dafault_Balance_Tree)
{
    ASSERT_NO_THROW(TBalanceTree bt);
}

TEST(TBalanceTree, Can_Insert_Record_In_Balance_Tree)
{
	TBalanceTree bt;

    ASSERT_NO_THROW(bt.InsRecord("1", nullptr));
}

TEST(TBalanceTree, Cant_Insert_Record_With_Existing_Key)
{
	TBalanceTree bt;
	bt.InsRecord("1", nullptr);
	bt.InsRecord("2", nullptr);
	bt.InsRecord("3", nullptr);

    ASSERT_ANY_THROW(bt.InsRecord("1", nullptr));
}

TEST(TBalanceTree, Can_Find_Record_In_Balance_Tree)
{
	TBalanceTree bt;
	bt.InsRecord("1", nullptr);
	bt.InsRecord("2", nullptr);
	bt.InsRecord("3", nullptr);

    ASSERT_NO_THROW(bt.FindRecord("1"));
}

TEST(TBalanceTree, Cant_Find_Record_In_Empty_Balance_Tree)
{
	TBalanceTree bt;

    ASSERT_ANY_THROW(bt.FindRecord("1"));
}

TEST(TBalanceTree, Cant_Find_Record_With_No_Existing_Key)
{
	TBalanceTree bt;
	bt.InsRecord("1", nullptr);

    ASSERT_ANY_THROW(bt.FindRecord("2"));
}

TEST(TBalanceTree, Determine_When_Balance_Tree_Is_Empty)
{
	TBalanceTree bt;

    EXPECT_EQ(bt.IsEmpty(), 1);
}

TEST(TBalanceTree, Balance_Tree_Sorted_With_Addition)
{
	TBalanceTree bt;
	bt.InsRecord("3", nullptr);
	bt.InsRecord("1", nullptr);
	bt.InsRecord("4", nullptr);
	bt.InsRecord("2", nullptr);

	bt.Reset();
	EXPECT_EQ(bt.GetKey(), "1");
	bt.GoNext();
	EXPECT_EQ(bt.GetKey(), "2");
	bt.GoNext();
	EXPECT_EQ(bt.GetKey(), "3");
	bt.GoNext();
	EXPECT_EQ(bt.GetKey(), "4");
	bt.GoNext();

    EXPECT_EQ(bt.IsTabEnded(), 1);
}

TEST(TBalanceTree, Cant_Delete_Record_In_Empty_Balance_Tree)
{
	TBalanceTree bt;

    ASSERT_ANY_THROW(bt.DelRecord("1"));
}

TEST(TBalanceTree, Cant_Delete_Record_With_No_Existing_Key)
{
	TBalanceTree bt;
	bt.InsRecord("1", nullptr);

    ASSERT_ANY_THROW(bt.DelRecord("2"));
}

TEST(TBalanceTree, Can_Delete_Record)
{
	TBalanceTree bt;
	bt.InsRecord("1", nullptr);

    ASSERT_NO_THROW(bt.DelRecord("1"));
}

TEST(TBalanceTree, Delete_Record_Is_Correct)
{
    TBalanceTree bt;
    bt.InsRecord("1", nullptr);
    bt.InsRecord("2", nullptr);
    bt.InsRecord("3", nullptr);

    bt.DelRecord("1");
    bt.DelRecord("2");
    bt.DelRecord("3");

    EXPECT_EQ(1, bt.IsEmpty());
}

TEST(TBalanceTree, Remove_Dont_Break_Sort_Table)
{
    TBalanceTree bt;
    bt.InsRecord("4", nullptr);
    bt.InsRecord("3", nullptr);
    bt.InsRecord("1", nullptr);
	bt.InsRecord("2", nullptr);

    bt.DelRecord("2");

    bt.Reset();
    EXPECT_EQ(bt.GetKey(), "1");
    bt.GoNext();
    EXPECT_EQ(bt.GetKey(), "3");
    bt.GoNext();
    EXPECT_EQ(bt.GetKey(), "4");
}

TEST(TBalanceTree, Remove_Record_With_The_Least_Key_Dont_Break_Table)
{
    TBalanceTree bt;
    bt.InsRecord("4", nullptr);
    bt.InsRecord("3", nullptr);
    bt.InsRecord("1", nullptr);
    bt.InsRecord("2", nullptr);

    bt.DelRecord("1");

    bt.Reset();
    EXPECT_EQ(bt.GetKey(), "2");
    bt.GoNext();
    EXPECT_EQ(bt.GetKey(), "3");
    bt.GoNext();
    EXPECT_EQ(bt.GetKey(), "4");
}

TEST(TBalanceTree, Remove_Record_With_The_Greatest_Key_Dont_Break_Table)
{
    TBalanceTree bt;
    bt.InsRecord("4", nullptr);
    bt.InsRecord("3", nullptr);
    bt.InsRecord("1", nullptr);
    bt.InsRecord("2", nullptr);

    bt.DelRecord("4");

    bt.Reset();
    EXPECT_EQ(bt.GetKey(), "1");
    bt.GoNext();
    EXPECT_EQ(bt.GetKey(), "2");
    bt.GoNext();
    EXPECT_EQ(bt.GetKey(), "3");
}

TEST(TBalanceTree, Remove_Record_With_Two_Child_Dont_Break_Table)
{
    TBalanceTree bt;
    bt.InsRecord("3", nullptr);
    bt.InsRecord("1", nullptr);
    bt.InsRecord("4", nullptr);
    bt.InsRecord("2", nullptr);

    bt.DelRecord("3");

    bt.Reset();
    EXPECT_EQ(bt.GetKey(), "1");
    bt.GoNext();
    EXPECT_EQ(bt.GetKey(), "2");
    bt.GoNext();
    EXPECT_EQ(bt.GetKey(), "4");
}


