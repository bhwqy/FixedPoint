cmake_minimum_required(VERSION 3.0)
project(fixed16_16_raw)
include_directories(${PROJECT_SOURCE_DIR}/include)

enable_testing()
    
find_package(GTest CONFIG REQUIRED)

set(CMAKE_BUILD_TYPE Release)
add_executable(main src/test.cpp)
target_link_libraries(main PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

add_test(AllTestsInMain main)
