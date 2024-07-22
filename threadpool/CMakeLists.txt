cmake_minimum_required(VERSION 3.5)

project(threadpool)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

file(GLOB THREADPOOL_SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)

add_library(${PROJECT_NAME} ${THREADPOOL_SRC_FILES})
