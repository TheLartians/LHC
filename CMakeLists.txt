cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# ---- Project ----
project(LarsHeaderCollection CXX)

if(${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif()

# ---- Configuration variables ----
set(LHC_TEST FALSE CACHE BOOL "build the Lars' Header Collection tests")

# ---- Create library ----
FILE(GLOB LarsHeaders "${CMAKE_CURRENT_SOURCE_DIR}/include/lars/*.h")
add_library(LarsHeaderCollection EXCLUDE_FROM_ALL ${LarsHeaders})
SET_TARGET_PROPERTIES(LarsHeaderCollection PROPERTIES LINKER_LANGUAGE CXX)

set(LHC_LIBRARY LarsHeaderCollection CACHE INTERNAL "The Lars' Header Collection (LHC) Library")

# ---- Tests ----
IF(LHC_TEST)
  include((${CMAKE_CURRENT_SOURCE_DIR}/cmake/googletest.cmake)
  
ENDIF()
