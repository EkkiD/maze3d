#ifndef __TEST_OPENGL_HPP__
#define __TEST_OPENGL_HPP__
#include <GL/glew.h>
#include <glfw3.h>
GLFWwindow* initGL(); 

void initPrimitives();
void initCube();

extern GLuint G_CUBE_VAO;

#endif

