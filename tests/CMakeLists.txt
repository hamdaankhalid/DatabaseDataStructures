cmake_minimum_required(VERSION 3.21)

set(Sources 
  tree-tests.cpp
  bloomfilter-tests.cpp
)

add_executable(database_data_structures_tests ${Sources}) 
 
target_link_libraries(
  database_data_structures_tests PUBLIC 
  gtest_main 
  database_data_structures
)

add_test(NAME database_data_structures_tests COMMAND database_data_structures_tests)
