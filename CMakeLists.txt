cmake_minimum_required(VERSION 4.1.1)
project(ray-tracing VERSION 1.0.0 
                    DESCRIPTION "Basic Ray Tracer"
                    LANGUAGES CXX)

find_package(OpenMP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(ray-tracing src/main.cpp src/scenes.cpp)

target_include_directories(ray-tracing PRIVATE include)
target_link_libraries(ray-tracing PRIVATE OpenMP::OpenMP_CXX)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/renders)

target_compile_definitions(ray-tracing PRIVATE
    PROJECT_ROOT="${CMAKE_SOURCE_DIR}"
    RENDER_DIR="${CMAKE_SOURCE_DIR}/renders"
    LOG_FILE="${CMAKE_SOURCE_DIR}/render_log.csv"
)