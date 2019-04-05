cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# ---- Project ----

project(Tests CXX)

# ---- CXX Flags ----

if(NOT CMAKE_CXX_STANDARD GREATER 17)
  set(CMAKE_CXX_STANDARD 17)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

# ---- Requires ----

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  find_package(LHC REQUIRED)
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/get_catch2.cmake)

# ---- Create binary ----

file(GLOB lhc_test_sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(lhc-tests ${lhc_test_sources})
add_dependencies(lhc-tests catch2-project)
target_link_libraries(lhc-tests catch2)
target_link_libraries(lhc-tests LHC)

# ---- Add tests ----

ENABLE_TESTING() 
ADD_TEST(lhc lhc-tests)

