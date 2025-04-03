cmake_minimum_required(VERSION 3.10)

project(biprcnv)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE DEBUG)

find_package(SFML 2.5 COMPONENTS system audio REQUIRED)

file(GLOB projectSrcs *.cpp)

add_executable(${PROJECT_NAME} ${projectSrcs})

target_link_libraries(${PROJECT_NAME} sfml-system sfml-audio )
