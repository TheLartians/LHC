cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# ---- Project ----
project(LarsHeaderCollection CXX)

if(${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif()

# ---- Configuration variables ----
set(LHC_TEST FALSE CACHE BOOL "build the Lars' Header Collection tests")

# ---- Minimum CXX ----
if(NOT CMAKE_CXX_STANDARD GREATER 17)
  set(CMAKE_CXX_STANDARD 17)
endif()


# ---- Create library ----
FILE(GLOB LarsHeaders "${CMAKE_CURRENT_SOURCE_DIR}/include/lars/*.h")
add_library(LarsHeaderCollection EXCLUDE_FROM_ALL ${LarsHeaders})
SET_TARGET_PROPERTIES(LarsHeaderCollection PROPERTIES LINKER_LANGUAGE CXX)

# ---- Export ----
set(LHC_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include/" CACHE INTERNAL "The Lars' Header Collection (LHC) include dir")

# ---- Tests ----
IF(LHC_TEST)
  set(CMAKE_CXX_STANDARD 17)  
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/get_catch2.cmake)
  file(GLOB lhc_test_sources ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)
  add_executable(lhc-tests ${lhc_test_sources})
  include_directories(${LHC_INCLUDE_DIRS})
  add_dependencies(lhc-tests catch2-project)
  target_link_libraries(lhc-tests catch2)        
ENDIF()

