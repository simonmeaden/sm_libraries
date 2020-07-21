
add_executable(qcircularbuffer tst_qcircularbuffer.cpp)
target_link_libraries(qcircularbuffer Qt5::Core gtest_main)
target_include_directories(qcircularbuffer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
add_test(NAME qcircularbuffer_tst COMMAND qcircularbuffer)
