set(HEADER_LIST "${DatabaseDataStructures_SOURCE_DIR}/include/database-data-structures/data-structures.hpp")

add_library(database_data_structures STATIC binary-search-tree.cpp red-black-tree.cpp ${HEADER_LIST})

target_include_directories(database_data_structures PUBLIC ../include)

target_compile_features(database_data_structures PUBLIC cxx_std_17)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}
)
