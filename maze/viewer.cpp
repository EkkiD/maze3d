#include <maze/viewer.hpp>

#include <glfw3.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
 
#include <common/shader.hpp>

int Viewer::run(){
    const GLuint shaderAttr = 0;

    auto window = initGL(); 
    if (window == nullptr) { return -1; }

    GLuint programID = LoadShaders( "vertex.glsl", "fragment.glsl");
    const GLuint MVPId = glGetUniformLocation(programID, "MVP");

    glm::mat4 MVP = getMVP();

    // Vertex Array must be bound before this call. 
    const GLuint vertexarray  = setupVertexArray();
    const GLuint vertexbuffer = setupVertexBuffer(shaderAttr);

    do {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(programID);

        glUniformMatrix4fv(MVPId, 1, GL_FALSE, &MVP[0][0]);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && 
            glfwWindowShouldClose(window) == 0);

    cleanup(vertexbuffer, programID, vertexarray);
    return 0;
}

GLuint Viewer::setupVertexArray() {
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    return VertexArrayID;
}

glm::mat4 Viewer::getMVP() {
    glm::mat4 proj = glm::perspective(1.04719f, 4.0f/4.0f, 0.1f, 1000.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(4,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0));
    glm::mat4 model = glm::mat4(1.0f);
    return proj * view * model;
}

GLuint Viewer::setupVertexBuffer(const GLuint shaderAttr) {
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    // {{{ Fill in the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

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

    return vertexbuffer;
}

void Viewer::cleanup(GLuint vertexbuffer, GLuint programID, GLuint vertexarray) {
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteVertexArrays(1, &vertexarray);
    glDeleteProgram(programID);
    glfwTerminate();
}
