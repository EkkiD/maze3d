#include <iostream>

#include <GL/glew.h>

#include <glfw3.h>
GLFWwindow* window;

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

 
#include <common/shader.hpp>

int initGL() {
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
    
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr<<"Failed to init GLEW"<<std::endl;
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    return 0;
}

int main(){
    auto x = 15;
    std::cout<<x<<std::endl;
    const unsigned int shaderAttr = 0;

    int r = initGL(); 
    if (r < 0) { return -1; }

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint programID = LoadShaders( "vertex.glsl", "fragment.glsl");
    GLuint MVPId = glGetUniformLocation(programID, "MVP");

    glm::mat4 proj = glm::perspective(60.0f, 4.0f/4.0f, 0.1f, 1000.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(4,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0));
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 MVP = proj * view * model;


    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };
    static const GLushort g_element_buffer_data[] = { 0, 1, 2 };

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    // {{{ Fill in the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    // }}}

    // Set the state for the vertex array object before the render loop! Yayyyy
    glEnableVertexAttribArray(shaderAttr);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        shaderAttr, // attribute 0
        3, // size
        GL_FLOAT, // type
        GL_FALSE, //normalized?
        0, //stride
        (void*)0 //array buffer offset
    );


    do {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(programID);

        glUniformMatrix4fv(MVPId, 1, GL_FALSE, &MVP[0][0]);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && 
            glfwWindowShouldClose(window) == 0);


    glDeleteBuffers(1, &vertexbuffer);
    glDeleteProgram(programID);
    glDeleteVertexArrays(1, &VertexArrayID);
    glfwTerminate();

    return 0;
}
