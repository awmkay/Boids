cmake_minimum_required(VERSION 3.21)

# Project name
set(EXECUTABLE_NAME Boids)
project(${EXECUTABLE_NAME} LANGUAGES CXX)

# Set cmake options
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

# Include SFML
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Adding code and linking lbiraries
set(SOURCES
	src/main.cpp)
include_directories(include)
include_directories(glm)
add_executable(${EXECUTABLE_NAME} ${SOURCES})
target_link_libraries(${EXECUTABLE_NAME} PRIVATE sfml-graphics)
target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_std_17)

# Not sure what this does
install(TARGETS ${EXECUTABLE_NAME})
