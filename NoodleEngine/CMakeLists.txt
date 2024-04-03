# CMakeList.txt : CMake project for NoodleEngine, include source and define
# project specific logic here.
#

set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static")

# Add source to this project's executable.
add_executable (NoodleEngine "NoodleEngine.cpp" "NoodleEngine.h"   "../includes/shader_s.h" "stb_image.cpp"    "Planetary.h" "Simulation.h" "CelestialBody.h" "CelestialBody.cpp" "GravityPivot.h" "GravityPivot.cpp" "Satellite.h" "Satellite.cpp" "Line.h" "Line.cpp"    "CameraController.h" "CameraController.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET NoodleEngine PROPERTY CXX_STANDARD 20)
endif()

include_directories(C:/DEV/GraphicsCookbook/GameEngines/NoodleEngine/includes)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(NoodleEngine PRIVATE glfw)

find_package(glad CONFIG REQUIRED)
target_link_libraries(NoodleEngine PRIVATE glad::glad)

find_package(glm CONFIG REQUIRED)
target_link_libraries(NoodleEngine PRIVATE glm::glm)