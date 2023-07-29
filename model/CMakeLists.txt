project(rpg_model)

set(${PROJECT_NAME}_SOURCES CoreItem.cpp Hero.cpp Stats.cpp Class.cpp)

if (BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_SOURCES})
    add_compile_definitions(RPG_BUILD)
else()
    add_library(rpg_cpp STATIC ${${PROJECT_NAME}_SOURCES})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})