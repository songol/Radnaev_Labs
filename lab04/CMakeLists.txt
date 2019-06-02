cmake_minimum_required(VERSION 3.12.1)
project(lab04)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/../)

add_executable(lab04 main.cpp CSV_iterator.h CSVParser.h)
find_package(GTest REQUIRED)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} pthread)