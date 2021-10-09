cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(LHCTests LANGUAGES CXX)

# ---- Options ----

option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)
option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

cpmaddpackage("gh:catchorg/Catch2@2.13.7")
cpmaddpackage("gh:TheLartians/Format.cmake@1.7.0")

if(TEST_INSTALLED_VERSION)
  find_package(LHC REQUIRED)
else()
  cpmaddpackage(NAME LHC SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
endif()

# ---- Create binary ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
add_executable(LHCTests ${sources})
target_link_libraries(LHCTests Catch2::Catch2 LHC::LHC)
set_target_properties(LHCTests PROPERTIES CXX_STANDARD 17)

# enable compiler warnings
if(NOT TEST_INSTALLED_VERSION)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES
                                              "GNU")
    target_compile_options(LHC INTERFACE -Wall -Wpedantic -Wextra -Werror
                                         -Werror=deprecated)
  elseif(MSVC)
    target_compile_options(LHC INTERFACE /W4 /WX)
    target_compile_definitions(LHCTests PUBLIC DOCTEST_CONFIG_USE_STD_HEADERS)
  endif()
endif()

# ---- Add LHCTests ----

enable_testing()
add_test(LHCTests LHCTests)

# ---- code coverage ----

if(ENABLE_TEST_COVERAGE)
  target_compile_options(LHC INTERFACE -O0 -g -fprofile-arcs -ftest-coverage)
  target_link_options(LHC INTERFACE -fprofile-arcs -ftest-coverage)
endif()
