#include<gtest/gtest.h>
#include <database-data-structures/data-structures.hpp>


TEST(BST, Insert)   {
  DatabaseDataStructure::BinarySearchTree bst;
  bst.add(1);
  EXPECT_TRUE(bst.find(1));
}

TEST(BST, Find)   {
  DatabaseDataStructure::BinarySearchTree bst;
  EXPECT_FALSE(bst.find(1));
  bst.add(1);
  EXPECT_TRUE(bst.find(1));
}

TEST(RBL, Insert)   {
  DatabaseDataStructure::RedBlackTree rbl;
  rbl.add(1);
  EXPECT_TRUE(rbl.find(1));
}

TEST(RBL, Find)   {
  DatabaseDataStructure::RedBlackTree rbl;
  EXPECT_FALSE(rbl.find(1));
  rbl.add(1);
  EXPECT_TRUE(rbl.find(1));
}

