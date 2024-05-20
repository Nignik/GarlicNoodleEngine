cmake_minimum_required(VERSION 3.20)

# Include directories for the project
include_directories(${PROJECT_SOURCE_DIR}/includes)

add_executable(NoodleEngine
        "NoodleEngine.cpp"
        "NoodleEngine.h"
        "stb_image.cpp"
        "Line.cpp"
        "CameraController.cpp"
        "Camera.cpp"
        "imgui_impl_glfw.cpp"
        "imgui_impl_opengl3.cpp"
        "gravity/GravitySimulation.h"
        "gravity/CelestialBody.cpp"
        "gravity/GravityPivot.cpp"
        "gravity/Satellite.cpp"
        "gravity/GravitySimulation.cpp"
  "NoodleGui.h" "NoodleGui.cpp")
