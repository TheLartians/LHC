cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(LarsHeaderCollection CXX)

if(${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif()

FILE(GLOB LarsHeaders "${CMAKE_CURRENT_SOURCE_DIR}/include/lars/*.h")
add_library(LarsHeaderCollection EXCLUDE_FROM_ALL ${LarsHeaders})

set(LHC_LIBRARY LarsHeaderCollection CACHE INTERNAL "The LarsHeaderCollection (LHC Library)")

