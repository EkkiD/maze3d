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

static const GLfloat g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f
	};

	static const GLfloat g_color_buffer_data[] = { 
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f
	};
    
    static const GLushort g_elem_array[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
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

GLuint setupColorBuffer(const GLuint shaderAttr) {
    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    // {{{ Fill in the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_elem_array), g_elem_array , GL_STATIC_DRAW);
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
