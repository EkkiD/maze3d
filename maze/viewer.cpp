#include <maze/viewer.hpp>

#include <glfw3.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
 
#include <common/shader.hpp>

int Viewer::init(){
    window = initGL(); 
    if (window == nullptr) { return -1; }
    return 0;
}

int Viewer::run(){
    GLuint programID = LoadShaders( "vertex.glsl", "fragment.glsl");
    const GLuint MVPId = glGetUniformLocation(programID, "MVP");

    glm::mat4 MVP = getMVP();

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

        glUniformMatrix4fv(MVPId, 1, GL_FALSE, &MVP[0][0]);

        scene.render(MVP);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && 
            glfwWindowShouldClose(window) == 0);

    cleanup(programID);
    return 0;
}

glm::mat4 Viewer::getMVP() {
    glm::mat4 proj = glm::perspective(1.04719f, 4.0f/4.0f, 0.1f, 1000.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(4,3,-3), glm::vec3(0,0,0), glm::vec3(0,1,0));
    glm::mat4 model = glm::mat4(1.0f);
    return proj * view * model;
}


void Viewer::cleanup(GLuint programID) {
    glDeleteProgram(programID);
    glfwTerminate();
}
