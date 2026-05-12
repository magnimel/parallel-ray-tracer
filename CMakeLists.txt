cmake_minimum_required(VERSION 3.28.3)
project(ray-tracing VERSION 1.0.0 
                    DESCRIPTION "Parallel Monte Carlo Path Tracer"
                    LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(OpenMP REQUIRED)

option(TRACY_ENABLE "Enable Tracy profiling" OFF)

if(TRACY_ENABLE)
    add_subdirectory(external/tracy)
endif()

add_executable(ray-tracing
    src/main.cpp
    src/scenes.cpp
)

target_include_directories(ray-tracing PRIVATE
    include
)

target_link_libraries(ray-tracing PRIVATE
    OpenMP::OpenMP_CXX
)

if(TRACY_ENABLE)
    target_link_libraries(ray-tracing PRIVATE Tracy::TracyClient)

    target_sources(ray-tracing PRIVATE
        src/tracy_memory.cpp
    )

    target_compile_definitions(ray-tracing PRIVATE
        TRACY_ENABLE
    )
endif()

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/renders)

target_compile_definitions(ray-tracing PRIVATE
    PROJECT_ROOT="${CMAKE_SOURCE_DIR}"
    RENDER_DIR="${CMAKE_SOURCE_DIR}/renders"
    LOG_FILE="${CMAKE_SOURCE_DIR}/render_log.csv"
)
