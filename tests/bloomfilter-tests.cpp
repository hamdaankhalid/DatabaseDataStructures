#include<gtest/gtest.h>
#include <database-data-structures/data-structures.hpp>
#include<functional>
#include<string>

TEST(Bloomfilter, findExisting) {
  std::hash<std::string> h;
  DatabaseDataStructure::BloomFilter bf(1, {h});
  bf.add("spark");
  EXPECT_TRUE(bf.does_probably_exist("spark"));
}
