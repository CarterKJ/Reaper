cmake_minimum_required(VERSION 3.24)
project(reaper C)

set(CMAKE_C_STANDARD 11)

add_executable(reaper main.c core/core.c core/core.h modules/hash_crack/hash_crack.c modules/hash_crack/hash_crack.h)
include_directories(${PROJECT_SOURCE_DIR})
