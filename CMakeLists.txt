cmake_minimum_required(VERSION 3.10)

project(Calc VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/include/calc-llvm/)
# include_directories($ENV{HOME}/code/llvm-project/llvm/include/)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_libs support core irreader)


add_executable(Calc src/main.cpp src/Lexer.cpp)
target_link_libraries(Calc ${llvm_libs})
