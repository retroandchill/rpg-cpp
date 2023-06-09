cmake_minimum_required(VERSION 3.25)
project(rpg-cpp)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(RPG_STANDALONE ON)
else()
    set(RPG_STANDALONE OFF)
endif()

if (EMSCRIPTEN)
    set(BUILD_SHARED_LIBS_DEFAULT OFF)
else()
    if (MINGW)
        set(BUILD_SHARED_LIBS_DEFAULT OFF)
    else()
        set(BUILD_SHARED_LIBS_DEFAULT ON)
    endif()
endif()

option(BUILD_SHARED_LIBS "rpg-cpp: build shared libs" ${BUILD_SHARED_LIBS_DEFAULT})
if (BUILD_SHARED_LIBS)
    add_compile_definitions(RPG_SHARED)
endif()

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(model)