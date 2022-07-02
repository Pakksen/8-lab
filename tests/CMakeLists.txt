add_subdirectory(googletest)
include_directories(..)
add_executable(test tests.cpp)
target_link_libraries(test polish gtest gtest_main)