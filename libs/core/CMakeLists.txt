################################################################################
# F E T C H   C O R E   L I B R A R Y
################################################################################
cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
project(fetch-core)

# CMake Configuration
include(${FETCH_ROOT_CMAKE_DIR}/BuildTools.cmake)

# Compiler Configuration
setup_compiler()

setup_library(fetch-core)
target_link_libraries(fetch-core PUBLIC fetch-vectorise)

add_test_target()

add_subdirectory(benchmark)

#if(FETCH_CLANG_TIDY_CFG)
#  message(STATUS "Whoop whoop")
#
#  set_target_properties(
#    fetch-core PROPERTIES
#    CXX_CLANG_TIDY "${FETCH_CLANG_TIDY_CFG}"
#  )
#endif(FETCH_CLANG_TIDY_CFG)
