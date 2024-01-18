cmake_minimum_required(VERSION 3.16)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(InSourceGuard)

project(
  "gpu-x"
  VERSION 0.1.0
  DESCRIPTION "Cross platform, cross vendor GPU code"
  LANGUAGES CXX)

include(CxxStandard)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(GPUX_VENDOR "The vendor to build gpu-x for, should equal AMD or NVIDIA."
       "Unspecified")
option(GPUX_BUILD_TESTS "If ON, gpu-x will build all tests." OFF)

if(NOT ${GPUX_VENDOR} STREQUAL "AMD" AND NOT ${GPUX_VENDOR} STREQUAL "NVIDIA")
  message(FATAL_ERROR "please set GPUX_VENDOR to 'AMD' or 'NVIDIA'")
endif()

set(SOURCES "")
if(${GPUX_VENDOR} STREQUAL "AMD")
  list(APPEND SOURCES src/amd/amd_runtime.cc)
else()
  list(APPEND SOURCES src/nvidia/nvidia_runtime.cc)
endif()

add_library(gpux ${SOURCES})
if(${BUILD_SHARED_LIBS})
  target_compile_definitions(gpux PRIVATE GPUX_BUILD_SHARED)
endif()
target_include_directories(
  gpux PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
              $<INSTALL_INTERFACE:include>)

if(${GPUX_VENDOR} STREQUAL "AMD")
  find_package(hip REQUIRED)
  find_package(rocblas REQUIRED)
  target_link_libraries(gpux PUBLIC hip::host roc::rocblas)
  target_compile_definitions(gpux PUBLIC __GPUX_PLATFORM_AMD__)
elseif(${GPUX_VENDOR} STREQUAL "NVIDIA")
  find_package(CUDAToolkit REQUIRED)
  target_link_libraries(gpux PUBLIC CUDA::cudart CUDA::cublas)
  target_compile_definitions(gpux PUBLIC __GPUX_PLATFORM_NVIDIA__)
endif()

include(CompileFlags)
apply_compilation_flags(gpux)
