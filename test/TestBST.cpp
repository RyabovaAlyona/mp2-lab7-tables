#include <gtest.h>
#include <string>
#include <iostream>

#include "TTreeNode.h"
#include "TTreeTable.h"


TEST(TTreeNode, Can_Create_Dafault_Tree_Node)
{
    ASSERT_NO_THROW(TTreeNode ttn);
}

TEST(TTreeNode, Can_Get_Left_From_Tree_Node)
{
    TTreeNode left("", nullptr, nullptr, nullptr);
    TTreeNode node("", nullptr, &left, nullptr);

    EXPECT_EQ(node.GetLeft(), &left);
}

TEST(TTreeNode, Can_Get_Right_From_Tree_Node)
{
    TTreeNode right("", nullptr, nullptr, nullptr);
    TTreeNode node("", nullptr, nullptr, &right);

    EXPECT_EQ(node.GetRight(), &right);
}

TEST(TTreeTable, Can_Create_Tree_Table) {
	ASSERT_NO_THROW(TTreeTable());
}

TEST(TTreeTable, Can_Insert_Record_Into_Tree_Table)
{
    TTreeTable tree;

    ASSERT_NO_THROW(tree.InsRecord("1", nullptr));
}

TEST(TTreeTable, Cant_Insert_Record_When_Key_Exist)
{
    TTreeTable tree;
	tree.InsRecord("1", nullptr);

    ASSERT_ANY_THROW(tree.InsRecord("1", nullptr));
}

TEST(TTreeTable, Can_Find_Record_Into_Tree_Table)
{
    TTreeTable tree;
	tree.InsRecord("1", nullptr);

    EXPECT_EQ(tree.FindRecord("1"), nullptr);
}

TEST(TTreeTable, Cant_Find_Record_When_It_Isnt_In_Table)
{
    TTreeTable tree;

    ASSERT_ANY_THROW(tree.FindRecord("3"));
}

TEST(TTreeTable, Can_Delete_Record_Into_Tree_Table)
{
    TTreeTable tree;
	tree.InsRecord("1", nullptr);

	ASSERT_NO_THROW(tree.DelRecord("1"));
}

TEST(TTreeTable, Cant_Delete_Record_When_It_Isnt_In_Table)
{
    TTreeTable tree;
	tree.InsRecord("1", nullptr);

	ASSERT_ANY_THROW(tree.DelRecord("2"));
}

TEST(TTreeTable, Delete_Record_Is_Correct)
{
    TTreeTable tree;
    tree.InsRecord("1", nullptr);
    tree.InsRecord("2", nullptr);
    tree.InsRecord("3", nullptr);

    tree.DelRecord("1");
    tree.DelRecord("2");
    tree.DelRecord("3");

    EXPECT_EQ(1, tree.IsEmpty());
}

TEST(TTreeTable, Remove_Dont_Break_Sort_Table)
{
    TTreeTable tree;
    tree.InsRecord("4", nullptr);
    tree.InsRecord("3", nullptr);
    tree.InsRecord("1", nullptr);
	tree.InsRecord("2", nullptr);

    tree.DelRecord("2");

    tree.Reset();
    EXPECT_EQ(tree.GetKey(), "1");
    tree.GoNext();
    EXPECT_EQ(tree.GetKey(), "3");
    tree.GoNext();
    EXPECT_EQ(tree.GetKey(), "4");
}

TEST(TTreeTable, Remove_Record_With_The_Least_Key_Dont_Break_Table)
{
    TTreeTable tree;
    tree.InsRecord("4", nullptr);
    tree.InsRecord("3", nullptr);
    tree.InsRecord("1", nullptr);
    tree.InsRecord("2", nullptr);

    tree.DelRecord("1");

    tree.Reset();
    EXPECT_EQ(tree.GetKey(), "2");
    tree.GoNext();
    EXPECT_EQ(tree.GetKey(), "3");
    tree.GoNext();
    EXPECT_EQ(tree.GetKey(), "4");
}

TEST(TTreeTable, Remove_Record_With_The_Greatest_Key_Dont_Break_Table)
{
    TTreeTable tree;
    tree.InsRecord("4", nullptr);
    tree.InsRecord("3", nullptr);
    tree.InsRecord("1", nullptr);
    tree.InsRecord("2", nullptr);

    tree.DelRecord("4");

    tree.Reset();
    EXPECT_EQ(tree.GetKey(), "1");
    tree.GoNext();
    EXPECT_EQ(tree.GetKey(), "2");
    tree.GoNext();
    EXPECT_EQ(tree.GetKey(), "3");
}

TEST(TTreeTable, Remove_Record_With_Two_Child_Dont_Break_Table)
{
    TTreeTable tree;
    tree.InsRecord("3", nullptr);
    tree.InsRecord("1", nullptr);
    tree.InsRecord("4", nullptr);
    tree.InsRecord("2", nullptr);

    tree.DelRecord("3");

    tree.Reset();
    EXPECT_EQ(tree.GetKey(), "1");
    tree.GoNext();
    EXPECT_EQ(tree.GetKey(), "2");
    tree.GoNext();
    EXPECT_EQ(tree.GetKey(), "4");
}







