cmake_minimum_required(VERSION 3.27)
project(cd_tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(../ tmc)

include(FetchContent)

FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# build gtest as static library
set(BUILD_SHARED_LIBS_OLD ${BUILD_SHARED_LIBS})
set(BUILD_SHARED_LIBS OFF)

FetchContent_MakeAvailable(googletest)

# restore old value
set(BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS_OLD})

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

function(add_gtest name src)
    add_executable(${name} "${src}")

    target_link_libraries(${name} gtest gtest_main collision_detector)
    # target_include_directories(${name} PUBLIC ../include/core ../include/demo)

    add_test(NAME ${name} COMMAND ${name})
endfunction()

add_gtest(Vec2Test src/CollisionDetector/Vec2Test.cpp)
add_gtest(Vec3Test src/CollisionDetector/Vec3Test.cpp)
add_gtest(CollisionDetectorTest src/CollisionDetector/CollisionDetectorTest.cpp)