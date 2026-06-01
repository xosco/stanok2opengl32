cmake_minimum_required(VERSION 3.15)
project(proxy_opengl32)

set(CMAKE_CXX_STANDARD 17)

# Для MinGW
set(CMAKE_SHARED_LIBRARY_PREFIX "")

add_library(opengl32 SHARED
    src/main.cpp
    src/gl_proxy.cpp
    src/overlay.cpp
    src/exports.def
)

target_include_directories(opengl32 PRIVATE
    src/
    C:/msys64/mingw64/include
)

target_link_libraries(opengl32
    -static-libgcc
    -static-libstdc++
    gdi32
    user32
)

set_target_properties(opengl32 PROPERTIES
    OUTPUT_NAME "opengl32"
    SUFFIX ".dll"
    PREFIX ""
)