cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# ---- Project ----

project(LHC 
  VERSION 0.4
  LANGUAGES CXX
)
# ---- Configuration variables ----

option(ENABLE_LHC_TESTS "Enable tests" OFF)

# ---- Include guards ----

if(TARGET LHC)
  return()
endif()

if(${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif()

# ---- Header target ----

FILE(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/include/lars/*.h")
add_library(LHC-headers EXCLUDE_FROM_ALL ${headers})
SET_TARGET_PROPERTIES(LHC-headers PROPERTIES LINKER_LANGUAGE CXX)

# ---- Create library ----

add_library(LHC INTERFACE)

target_include_directories(LHC
  INTERFACE 
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  "${PROJECT_BINARY_DIR}/LHCConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

# ---- Install ----

install(
  TARGETS LHC
  EXPORT LHCTargets
  LIBRARY DESTINATION lib COMPONENT Runtime
  ARCHIVE DESTINATION lib COMPONENT Development
  RUNTIME DESTINATION bin COMPONENT Runtime
  PUBLIC_HEADER DESTINATION include COMPONENT Development
  BUNDLE DESTINATION bin COMPONENT Runtime
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/LHCConfig.cmake.in"
  "${PROJECT_BINARY_DIR}/LHCConfig.cmake"
  INSTALL_DESTINATION lib/cmake/LHC
)

install(
  EXPORT LHCTargets 
  DESTINATION lib/cmake/LHC
)

install(
  FILES 
    "${PROJECT_BINARY_DIR}/LHCConfigVersion.cmake"
    "${PROJECT_BINARY_DIR}/LHCConfig.cmake"
  DESTINATION 
    lib/cmake/LHC
)

install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/include/
  DESTINATION include
)

# ---- Test ----

if(${ENABLE_LHC_TESTS})
  ENABLE_TESTING()  
  add_subdirectory(tests)  
endif()

