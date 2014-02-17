include_directories(${CMAKE_SOURCE_DIR}/sim/include)
include_directories(include)

add_library(simBase SHARED src/MCTrack.cxx src/evg.cxx src/evd.cxx src/ev3d.cxx)
add_library(simGeo SHARED src/Module.cxx src/TestVolume.cxx)

target_link_libraries(simGeo ${ROOT_LIBS})
target_link_libraries(simBase ${ROOT_LIBS} simGeo Geom RGL)
