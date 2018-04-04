cmake_minimum_required (VERSION 2.6)
Project (advgraph)

set (CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE advgraph_SOURCES "src/*.cpp")
file(GLOB_RECURSE advgraph_HEADERS "src/*.h")
include_directories("src")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
add_executable(advgraph ${advgraph_SOURCES})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(deps/glfw-3.2.1)
target_link_libraries(advgraph glfw)

find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(advgraph ${OPENGL_gl_LIBRARY})

include_directories(deps/glad/include)
add_subdirectory(deps/glad)
target_link_libraries(advgraph glad)

