
add_executable(circularbuffer tst_circularbuffer.cpp)
target_link_libraries(circularbuffer gtest_main)
target_include_directories(circularbuffer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
add_test(NAME circularbuffer_tst COMMAND circularbuffer)
