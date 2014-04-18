cmake_minimum_required(VERSION 2.8)
project(MAZE)

add_subdirectory (extern)

include_directories(
	extern/glfw-3.0.4/include/GLFW/
	extern/glm/
	extern/glew-1.10.0/include/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_1100
)

set (CMAKE_CXX_FLAGS "-g -Wall -std=c++11")

add_executable(test 
	test/test.cpp
    test/opengl.cpp
	common/shader.cpp
	common/shader.hpp
	
	test/fragment.glsl
	test/vertex.glsl
)
target_link_libraries(test ${ALL_LIBS})

add_executable(maze 
	maze/main.cpp
    maze/opengl.cpp
    maze/viewer.cpp
    maze/cube.cpp
    maze/node.cpp
	common/shader.cpp
	
	maze/fragment.glsl
	maze/vertex.glsl
)

target_link_libraries(maze ${ALL_LIBS})
