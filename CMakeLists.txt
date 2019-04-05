cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# ---- Project ----
project(LHC CXX)

if(${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif()

# ---- Configuration variables ----
set(LHC_TEST FALSE CACHE BOOL "build the Lars' Header Collection tests")

# ---- Minimum CXX ----
if(NOT CMAKE_CXX_STANDARD GREATER 17)
  set(CMAKE_CXX_STANDARD 17)
endif()

# ---- Header target ----
FILE(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/include/lars/*.h")
add_library(LHC-headers EXCLUDE_FROM_ALL ${headers})
SET_TARGET_PROPERTIES(LHC-headers PROPERTIES LINKER_LANGUAGE CXX)

# ---- Create library ----

add_library(LHC INTERFACE)

target_include_directories(LHC INTERFACE 
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${PROJECT_BINARY_DIR}/LHCConfigVersion.cmake"
    VERSION v0.1
    COMPATIBILITY AnyNewerVersion
)

# ---- Install ----

install(TARGETS LHC
    EXPORT LHCTargets
    LIBRARY DESTINATION lib COMPONENT Runtime
    ARCHIVE DESTINATION lib COMPONENT Development
    RUNTIME DESTINATION bin COMPONENT Runtime
    PUBLIC_HEADER DESTINATION include COMPONENT Development
    BUNDLE DESTINATION bin COMPONENT Runtime
)

# ---- Tests ----
IF(LHC_TEST)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/get_catch2.cmake)
  file(GLOB lhc_test_sources ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)
  add_executable(lhc-tests ${lhc_test_sources})
  add_dependencies(lhc-tests catch2-project)
  target_link_libraries(lhc-tests catch2)
  target_link_libraries(lhc-tests LHC)
ENDIF()

