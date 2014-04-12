#include <iostream>

#include <GL/glew.h>

#include <glfw3.h>
GLFWwindow* window;

#include <glm/vec3.hpp>

int main(){
    auto x = 15;
    std::cout<<x<<std::endl;

    if (!glfwInit()) {
        std::cerr<<"Failed to init GLFW"<<std::endl;
        return -1;
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
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    if (glewInit() != GLEW_OK) {
        std::cerr<<"Failed to init GLEW"<<std::endl;
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    do {
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && 
            glfwWindowShouldClose(window) == 0);


    glfwTerminate();

    return 0;
}
