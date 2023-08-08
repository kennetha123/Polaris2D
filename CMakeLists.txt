cmake_minimum_required(VERSION 3.10)

project(Polaris2D VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE CORE "core/src/*.cpp")
include_directories(${CMAKE_SOURCE_DIR}/core/header ${CMAKE_SOURCE_DIR}/deps/Stellar/code/headers)

add_library(Polaris2D SHARED ${CORE})
target_link_libraries(Polaris2D ${CMAKE_SOURCE_DIR}/deps/Stellar/bin/Stellar.lib)

