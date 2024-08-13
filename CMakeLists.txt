cmake_minimum_required(VERSION 3.28)
project(RaysGame)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
        GIT_TAG "5.0"
        GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)

add_executable(RaysGame main.cpp
        include/Entities.h
        src/Map.cpp
        include/Map.h
        src/Entities.cpp
        include/utils.h)
target_link_libraries(RaysGame PRIVATE raylib)
