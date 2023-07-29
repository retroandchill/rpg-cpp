project(ModelTests)

add_executable(${PROJECT_NAME} ModelTests.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC rpg_model Catch2::Catch2 Catch2::Catch2WithMain)

catch_discover_tests(${PROJECT_NAME})