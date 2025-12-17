cmake_minimum_required(VERSION 3.10)

project(BrainfuckCompiler)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(CORE_SOURCES
    src/core/bfrunner.cpp
    src/core/bfprompt.cpp
    src/core/bfinitialize.cpp
)

add_library(core STATIC ${CORE_SOURCES})

add_executable(bfi src/interpreter/bfi.cpp)
target_link_libraries(bfi core)

add_executable(
    bfdbg src/debugger/bfdbg.cpp
    src/Debugger/bfdbgrunner.cpp
    src/Debugger/bfdbgtui.cpp
)
target_link_libraries(bfdbg core)