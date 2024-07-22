cmake_minimum_required(VERSION 3.5)

project(threadpool_app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

add_executable(${PROJECT_NAME}
    main.cpp
)

add_subdirectory(${PROJECT_SOURCE_DIR}/threadpool)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/threadpool)
target_link_libraries(${PROJECT_NAME} PRIVATE threadpool)
