add_executable(lab3_oop lab3_main.cpp src/lab3_func.cpp)
add_executable(lab3_tests test/lab3_tests.cpp src/lab3_func.cpp)
target_link_libraries(lab3_tests GTest::gtest_main)