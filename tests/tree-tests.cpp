#include<gtest/gtest.h>
#include <database-data-structures/data-structures.hpp>


TEST(BST, Add)   {
  DatabaseDataStructure::BinarySearchTree bst;
  bst.add(1);
  bst.add(4);
  bst.add(5);
  
  EXPECT_TRUE(bst.find(1));
  EXPECT_TRUE(bst.find(4));
  EXPECT_TRUE(bst.find(5));
}

TEST(BST, Find)   {
  DatabaseDataStructure::BinarySearchTree bst;
  EXPECT_FALSE(bst.find(1));
  bst.add(1);
  bst.add(21);
  bst.add(2);
  
  EXPECT_TRUE(bst.find(1));
  EXPECT_TRUE(bst.find(21));
  EXPECT_TRUE(bst.find(2));

  EXPECT_FALSE(bst.find(-5));
  EXPECT_FALSE(bst.find(22));
}

TEST(BST, Remove)   {
  DatabaseDataStructure::BinarySearchTree bst;
  
  bst.add(1);
  bst.add(21);
  bst.add(2);
  
  bst.remove(21);
  EXPECT_FALSE(bst.find(21));
}

TEST(RBL, Add)   {
  DatabaseDataStructure::RedBlackTree rbl;
  
  EXPECT_FALSE(rbl.find(1));
  
  rbl.add(1);
  rbl.add(4);
  rbl.add(5);
  rbl.add(-3);
  rbl.add(-5);
  rbl.add(2);


  EXPECT_TRUE(rbl.find(1));
  EXPECT_TRUE(rbl.find(4));
  EXPECT_TRUE(rbl.find(-3));
  EXPECT_TRUE(rbl.find(-5));
  EXPECT_TRUE(rbl.find(2));
  EXPECT_TRUE(rbl.find(5));
}

// TEST(RBL, Find)   {
//   DatabaseDataStructure::RedBlackTree rbl;
//   EXPECT_FALSE(rbl.find(1));
//   rbl.add(1);
//   EXPECT_TRUE(rbl.find(1));
// }

