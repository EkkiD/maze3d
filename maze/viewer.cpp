#include <maze/viewer.hpp>

#include <glfw3.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
 
#include <common/shader.hpp>


GLuint G_MVP_ID = 0;
GLuint G_M_ID = 0;
GLuint G_V_ID = 0;

int Viewer::init(){
    window = initGL(); 
    if (window == nullptr) { return -1; }
    m_interaction.init(window);
    return 0;
}

int Viewer::run(){
    GLuint programID = LoadShaders( "vertex.glsl", "fragment.glsl");
    G_MVP_ID = glGetUniformLocation(programID, "MVP");
    G_V_ID = glGetUniformLocation(programID, "V");
    G_M_ID = glGetUniformLocation(programID, "M");
    GLuint lightPosId = glGetUniformLocation(programID, "LightPosition_world");
    auto lightPos = m_interaction.cameraLoc();
    setMVP();

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

        glUniformMatrix4fv(G_MVP_ID, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(G_V_ID, 1, GL_FALSE, &V[0][0]);
        glUniformMatrix4fv(G_M_ID, 1, GL_FALSE, &M[0][0]);
        glUniform3f(lightPosId, lightPos.x, lightPos.y, lightPos.z);

        //auto mvp = MVP * m_trackball.rotation();
        auto mvp = P * V * M * m_interaction.rotation();
        auto m =  M * m_interaction.rotation();
        m_maze.render(mvp, m);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && 
            glfwWindowShouldClose(window) == 0);

    cleanup(programID);
    return 0;
}

void Viewer::setMVP() {
    P = glm::perspective(1.04719f, 4.0f/4.0f, 0.1f, 1000.0f);
    V = glm::lookAt(m_interaction.cameraLoc(), glm::vec3(0,0,0), glm::vec3(0,1,0));
    M = glm::mat4(1.0f);
    MVP = P * V * M;
}

void Viewer::cleanup(GLuint programID) {
    glDeleteProgram(programID);
    glfwTerminate();
}
