cmake_minimum_required(VERSION 3.10)

project(Polaris2D VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE CORE "core/src/*.cpp" "core/header/*.h")
include_directories(${CMAKE_SOURCE_DIR}/core/headers)

add_executable(Polaris2D ${CORE})
