add_definitions(-DGLEW_STATIC)

include_directories(glm)

### GLFW ###

add_subdirectory (glfw-3.0.4)

include_directories(
	glfw-3.0.4/include/GLFW/
	glew-1.10.0/include/
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(OPENGL_LIBRARY
	${OPENGL_LIBRARY}
	-lGL -lGLU -lXrandr -lXext -lX11 -lrt
	${CMAKE_DL_LIBS}
	${GLFW_LIBRARIES}
)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

### GLEW ###

set(GLEW_SOURCE
	glew-1.10.0/src/glew.c
)

set(GLEW_HEADERS
)


add_library( GLEW_1100 STATIC
	${GLEW_SOURCE}
	${GLEW_INCLUDE}
)

target_link_libraries(GLEW_1100
	${OPENGL_LIBRARY}
	${EXTRA_LIBS}
)


