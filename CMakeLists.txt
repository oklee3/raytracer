cmake_minimum_required ( VERSION 3.1.0...4.0.0 )

project (raytracer LANGUAGES CXX )

set ( CMAKE_CXX_STANDARD          11 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )
set ( CMAKE_CXX_EXTENSIONS        OFF )

set (SOURCE_RAYTRACER
    src/main.cpp
    includes/vec3.h
)