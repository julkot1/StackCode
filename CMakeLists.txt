cmake_minimum_required(VERSION 3.15)
project(stcc LANGUAGES C CXX)

cmake_policy(SET CMP0135 NEW)
set(CMAKE_CXX_STANDARD 20)

set(LIBEDIT_INCLUDE_DIRS "/usr/include/editline")
set(LIBEDIT_LIBRARIES "/usr/lib/libedit.so")

# LLVM setup
find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

#Fetch cxxopts
include(FetchContent)
FetchContent_Declare(
        cxxopts
        GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
        GIT_TAG v3.1.1
)
FetchContent_MakeAvailable(cxxopts)


#Test setup
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_subdirectory(src)
