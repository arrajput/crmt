include_directories(${CMAKE_SOURCE_DIR}/reco/include)
include_directories(include)

add_library(recoBase SHARED src/Fiber.cxx src/Track.cxx src/Geometry.cxx src/Line.cxx)
add_library(recoParticle SHARED src/Detector.cxx src/FileManager.cxx src/RecoModule.cxx)
add_library(recoDisplay SHARED src/Viewer.cxx)

target_link_libraries(recoBase ${ROOT_LIBS})
target_link_libraries(recoDisplay ${ROOT_LIBS} recoBase)
target_link_libraries(recoParticle ${ROOT_LIBS} recoBase)
