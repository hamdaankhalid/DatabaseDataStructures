#include<gtest/gtest.h>
#include <database-data-structures/data-structures.hpp>

TEST(BinarySearchTreeTests, Insert)   {
  DatabaseDataStructure::BinarySearchTree bst;
  bst.add(1);
  EXPECT_TRUE(bst.find(1));
}

TEST(BinarySearchTreeTests, Find)   {
  DatabaseDataStructure::BinarySearchTree bst;
  EXPECT_FALSE(bst.find(1));
  bst.add(1);
  EXPECT_TRUE(bst.find(1));
}

TEST(BinarySearchTreeTests, Remove)   {
  DatabaseDataStructure::BinarySearchTree bst;
  bst.add(1);
  EXPECT_TRUE(bst.find(1));
  bst.remove(1);
  EXPECT_FALSE(bst.find(1));
}
