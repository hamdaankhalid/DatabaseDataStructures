#include<gtest/gtest.h>
#include <database-data-structures/data-structures.hpp>
#include<functional>
#include<string>

TEST(Bloomfilter, findexisting) {
  std::hash<std::string> h;
  DatabaseDataStructure::BloomFilter bf(100, {h});
  bf.add("spark");
  bf.add("bicup");
  bf.add("cup");
  EXPECT_TRUE(bf.does_probably_exist("spark"));
  EXPECT_TRUE(bf.does_probably_exist("bicup"));
  EXPECT_TRUE(bf.does_probably_exist("cup"));
}

TEST(Bloomfilter, cantfindnonexisting) {
  std::hash<std::string> h;
  DatabaseDataStructure::BloomFilter bf(100, {h});
  // adding spark and others to make sure we have one 
  // item and check if it can still function right
  bf.add("spark");
  bf.add("bicup");
  bf.add("cup");

  EXPECT_FALSE(bf.does_probably_exist("hamdaan"));
}
