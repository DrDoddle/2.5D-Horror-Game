cmake_minimum_required(VERSION 3.22)

project(DoomClone LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell CMake where SFML 2.5.1 is installed
set(SFML_DIR "C:/Libraries/SFML-3.0.0/lib/cmake/SFML")

set(SFML_STATIC_LIBRARIES ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

file(GLOB SOURCES
    "src/*.cpp"
    "src/*.hpp"
    "src/*.h"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()