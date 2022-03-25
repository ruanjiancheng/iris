cmake_minimum_required(VERSION 3.22)

project(iris)

set (CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(SRC_LIST application.cpp 
            src/Lexer/Lexer.cpp 
            src/Token/Token.cpp 
            src/Token/TokenReader.cpp 
            src/utils/utils.cpp 
            src/Parser/Parser.cpp 
            src/AST/ASTNode.cpp
            src/Script/Script.cpp)

message(STATUS "SRC_LIST: " ${SRC_LIST})

include_directories(include)

add_executable(main_cmake ${SRC_LIST})