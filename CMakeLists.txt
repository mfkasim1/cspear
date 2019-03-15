cmake_minimum_required(VERSION 3.5)
project(radopt)

# user defined variables:
# * NOOPENMP: if set to 1, it forces to not using OpenMP
# * PROFILING: if set to 1, set the profiling flag for gprof

# set the default build type as debug
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE DEBUG)
endif()

# set flags
set(CXX11_FLAGS "-std=c++11")
set(OPT_FLAGS "-O2")
set(DEBUG_FLAGS "-g")
set(PROFILING_FLAGS "-pg -no-pie")

# default flags to be used for all targets
set(CMAKE_CXX_FLAGS "${CXX11_FLAGS} ${OPT_FLAGS}")

# check for openmp
find_package(OpenMP)
if (OPENMP_FOUND AND NOT NOOPENMP)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

# check if the user wants to have the profiling mode
if (PROFILING)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PROFILING_FLAGS}")
endif (PROFILING)

# include directories
include_directories("include")

# add the executable
add_executable(a.out main.cc)

unset(CMAKE_BUILD_TYPE)
