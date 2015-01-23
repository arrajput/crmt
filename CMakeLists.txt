cmake_minimum_required(VERSION 2.8)
project(crmt)

## -- set some cmake variables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_CXX_FLAGS "-g -O3 -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})

## -- boost
find_package(Boost REQUIRED COMPONENTS program_options)
include_directories("${Boost_INCLUDE_DIRS}")
## -- prepare ROOT and inc and lib dirs
find_package(ROOT REQUIRED)
include_directories("${ROOT_INC_DIR}")
link_directories("${ROOT_LIB_DIR}")
## -- prepare project include and lib dirs
link_directories("${CMAKE_SOURCE_DIR}/lib")

include_directories("/usr/include")
include_directories("${CMAKE_SOURCE_DIR}/sim/include")
include_directories("${CMAKE_SOURCE_DIR}/reco/include")

add_subdirectory(reco)
add_subdirectory(sim)

add_executable(crmt crmt.cxx)
target_link_libraries(crmt ${ROOT_LIBS} simBase  recoParticle recoDisplay ${Boost_PROGRAM_OPTIONS_LIBRARY} simGeo recoBase)
