cmake_minimum_required(VERSION 3.17)
project(MarkLearningCPP VERSION 1.0)

# 输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Boost Support
find_package(Boost 1.74.0)
include_directories(${Boost_INCLUDE_DIRS})

# Self-Defined Support
add_subdirectory(templates)
list(APPEND EXTRA_LIBS templates)

# run
add_executable(MarkLearningCPP
        "problemsets/Acwing/3250. 通信网络/slt-topo.cpp"
        )

# target
target_link_libraries(MarkLearningCPP PUBLIC ${EXTRA_LIBS})
target_include_directories(MarkLearningCPP PUBLIC "${PROJECT_BINARY_DIR}")
