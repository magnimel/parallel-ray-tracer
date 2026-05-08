cmake_minimum_required(VERSION 4.1.1)
project(ray-tracing VERSION 1.0.0 
                    DESCRIPTION "Basic Ray Tracer"
                    LANGUAGES CXX)

find_package(OpenMP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(ray-tracing src/main.cpp)

target_include_directories(ray-tracing PRIVATE include)
target_link_libraries(ray-tracing PRIVATE OpenMP::OpenMP_CXX)


set(OUT_DIR ${CMAKE_SOURCE_DIR}/out)
file(MAKE_DIRECTORY ${OUT_DIR})

add_custom_command(
  OUTPUT ${OUT_DIR}/image.ppm
  COMMAND ray-tracing > ${OUT_DIR}/image.ppm
  DEPENDS ray-tracing
  COMMENT "Rendering image.ppm"
  VERBATIM
)

add_custom_target(render DEPENDS ${OUT_DIR}/image.ppm )