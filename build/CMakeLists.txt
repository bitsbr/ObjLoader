cmake_minimum_required(VERSION 3.5)

set( CMAKE_BUILD_TYPE Debug)
set( CMAKE_CXX_FLAGS   "${CMAKE_CXX_FLAGS} -std=c++14 -framework Opengl -lSDL2 -lGLEW"  )

file(GLOB myFiles   "../src/*.hpp" "../src/*.cpp" )
project( ObjLoader )

add_executable(    
    objLoader
    ${myFiles}
)