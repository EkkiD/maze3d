#include <iostream>
#include <test/opengl.hpp>
#include <glfw3.h>

GLFWwindow* initGL() {
    GLFWwindow* window;
    if (!glfwInit()) {
        std::cerr<<"Failed to init GLFW"<<std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1024, 768, "Test", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr<<"Failed to open GLFW window."<<std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr<<"Failed to init GLEW"<<std::endl;
        return nullptr;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    return window;
}
