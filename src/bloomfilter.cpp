#include <database-data-structures/data-structures.hpp>
#include <vector>
#include <string>


DatabaseDataStructure::BloomFilter::BloomFilter(int size, std::vector<std::hash> hashes): _bit_flowers(size, false), _hashers(hashes) {}

void DatabaseDataStructure::BloomFilter::add(std::string item) {
  for (auto hash_func: _hashers) {
    int hashed_inp = hash_func(item);
    _bit_flowers.at(hashed_inp) = true;
  }
}

bool DatabaseDataStructure::BloomFilter::does_probably_exist(std::string item) {
  for (auto hash_func: _hashers) {
    int hashed_inp = hash_func(item);
    if (!_bit_flowers.at(hashed_inp)) {
      return false;
    }
  }
  return true;
}
