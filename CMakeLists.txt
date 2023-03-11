cmake_minimum_required(VERSION 3.6)
project(ipctest)
include_directories(third_party/kproto/include /usr/include)

set(SOURCE_FILES
  main.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} -lzmq)