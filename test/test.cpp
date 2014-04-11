#include <iostream>
#include <GL/glew.h>

#include <glfw3.h>

#include <glm/vec3.hpp>
GLFWwindow* window;

int main(){
    std::cout<<"HELLO, WORLD"<<std::endl;
    auto x = 15;
    std::cout<<x<<std::endl;

    auto y = glm::vec3(0.0f, 0.1f, 0.4f);
    std::cout<<"DONE"<<std::endl;
}
