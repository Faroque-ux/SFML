cmake_minimum_required(VERSION 3.10)

project(sfml-project)

set(CMAKE_CXX_STANDARD 11)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(src/headers)

file(GLOB SOURCES "src/*.cpp" "src/sources/*.cpp")

add_executable(sfml-project ${SOURCES})

target_link_libraries(sfml-project sfml-graphics sfml-window sfml-system sfml-audio)