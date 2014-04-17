#include <test/opengl.hpp>
#include <iostream>

#include <GL/glew.h>
#include <glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
 
#include <common/shader.hpp>

    const GLfloat cube_verts[] = {
        // front
       -1.0f, -1.0f,  1.0,
        1.0f, -1.0f,  1.0,
        1.0f,  1.0f,  1.0,
       -1.0f,  1.0f,  1.0,
        //back
       -1.0f, -1.0f, -1.0,
        1.0f, -1.0f, -1.0,
        1.0f,  1.0f, -1.0,
       -1.0f,  1.0f, -1.0,
    };

    const GLfloat cube_colors[] = {
        // front
        1.0f,  0.0f,  0.0,
        0.0f,  1.0f,  0.0,
        0.0f,  0.0f,  1.0,
        1.0f,  1.0f,  1.0,
        //back
        1.0f,  0.0f,  0.0,
        0.0f,  1.0f,  0.0,
        0.0f,  0.0f,  1.0,
        1.0f,  1.0f,  1.0,
    };

    const GLushort cube_indices[] = {
        //front
        0, 1, 2,
        2, 3, 0,
        // top
        3, 2, 6,
        6, 7, 3,
        //back
        7, 6, 5,
        5, 4, 7,
        // bottom
        4, 5, 1,
        1, 0, 4,
        //left
        4, 0, 3,
        3, 7, 4,
        //right
        1, 5, 6,
        6, 2, 1,
    };

GLuint setupVertexArray() {
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    return VertexArrayID;
}

glm::mat4 getMVP() {
    glm::mat4 proj = glm::perspective(1.04719f, 4.0f/4.0f, 0.1f, 1000.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(4,3,-3), glm::vec3(0,0,0), glm::vec3(0,1,0));
    glm::mat4 model = glm::mat4(1.0f);
    return proj * view * model;
}

GLuint setupVertexBuffer(const GLuint shaderAttr) {
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    // {{{ Fill in the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_verts), cube_verts, GL_STATIC_DRAW);

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

GLuint setupColorBuffer(const GLuint shaderAttr) {
    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    // {{{ Fill in the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);

    // Set the state for the vertex array object before the render loop! Yayyyy
    glEnableVertexAttribArray(shaderAttr);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(
        shaderAttr, // attribute 0
        3, // size
        GL_FLOAT, // type
        GL_FALSE, //normalized?
        0, //stride
        (void*)0 //array buffer offset
    );

    return colorbuffer;
}

GLuint setupElementArray(){
	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices , GL_STATIC_DRAW);
    return elementbuffer;
}

void cleanup(GLuint vertexbuffer, GLuint programID, GLuint vertexarray) {
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteVertexArrays(1, &vertexarray);
    glDeleteProgram(programID);
    glfwTerminate();
}

int main(){
    const GLuint shaderAttr = 0;
    const GLuint colorAttr = 1;

    auto window = initGL(); 
    if (window == nullptr) { return -1; }

    GLuint programID = LoadShaders( "vertex.glsl", "fragment.glsl");
    const GLuint MVPId = glGetUniformLocation(programID, "MVP");

    glm::mat4 MVP = getMVP();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Vertex Array must be bound before this call. 
    const GLuint vertexarray  = setupVertexArray();
    const GLuint vertexbuffer = setupVertexBuffer(shaderAttr);
    const GLuint colorbuffer = setupColorBuffer(colorAttr);
    const GLuint elembuffer = setupElementArray();
    glBindVertexArray(0);

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

        glUniformMatrix4fv(MVPId, 1, GL_FALSE, &MVP[0][0]);

        glBindVertexArray(vertexarray);
        glDrawElements(GL_TRIANGLES,
                36,
                GL_UNSIGNED_SHORT,
                (void*)0
                );

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && 
            glfwWindowShouldClose(window) == 0);

    cleanup(vertexbuffer, programID, vertexarray);

    return 0;
}
