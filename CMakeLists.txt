cmake_minimum_required(VERSION 3.25)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
project(rpg-cpp)

set(CMAKE_CXX_STANDARD 17)

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

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out CACHE STRING "" )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out CACHE STRING "" )

add_subdirectory(model)

option(BUILD_TESTING "rpg-cpp: build the tests for the project" ON)
if (BUILD_TESTING)
    enable_testing()
    include(CTest)

    find_package(Catch2 REQUIRED)
    include(Catch)

    add_subdirectory(test)
endif()