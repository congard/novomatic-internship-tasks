cmake_minimum_required(VERSION 3.27)
project(t3_collision_detection)

set(CMAKE_CXX_STANDARD 20)

set(COLLISION_DETECTOR_LIB_SOURCES
        src/CollisionDetector/vec.h
        src/CollisionDetector/triangle.h
        src/CollisionDetector/CollisionDetector.h
        src/CollisionDetector/CollisionDetector.cpp
        src/CollisionDetector/vec2.h
        src/CollisionDetector/vec3.h)

add_library(collision_detector ${COLLISION_DETECTOR_LIB_SOURCES})
target_include_directories(collision_detector PUBLIC src)

if (ALGINE_PATH)
    message(STATUS "ALGINE_PATH specified: ${ALGINE_PATH}")

    # silence warnings from sol2
    add_compile_options(-Wno-unknown-warning-option)

    include("${ALGINE_PATH}/cmake/mold.cmake")
    try_use_mold()

    macro(set_global name value)
        set(${name} ${value} CACHE INTERNAL ${name})
    endmacro()

    # speedup compilation by disabling unnecessary features
    set_global(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF)
    set_global(ASSIMP_BUILD_ZLIB OFF)
    set_global(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
    set_global(ASSIMP_BUILD_TESTS OFF)
    set_global(LUA_ENABLE_SHARED OFF)

    add_subdirectory(${ALGINE_PATH} algine)

    set(VISUALIZER_SOURCES src/visualizer/Visualizer.cpp
            src/visualizer/VisualizerContent.h
            src/visualizer/VisualizerContent.cpp
            src/visualizer/ui/VisualizerLayer.h
            src/visualizer/ui/VisualizerLayer.cpp
            src/visualizer/ui/VisualizerScene.h
            src/visualizer/ui/VisualizerScene.cpp
            src/visualizer/ui/VisualizerWidget.cpp
            src/visualizer/ui/VisualizerWidget.h)

    add_executable(visualizer ${VISUALIZER_SOURCES})
    target_link_libraries(visualizer algine collision_detector)

    # TODO: windows support
else()
    message(STATUS "ALGINE_PATH is not specified. Visualizer will not be built.")
endif()
