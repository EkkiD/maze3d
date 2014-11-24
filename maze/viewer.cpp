#include <maze/viewer.hpp>

#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
 
#include <common/shader.hpp>
#include <maze/mazeShaders.hpp>

#include <chrono>
#include <thread>


GLuint G_MVP_ID = 0;
GLuint G_M_ID = 0;
GLuint G_V_ID = 0;
GLuint G_INVTRANSVM_ID = 0;
GLuint G_ALPHA_ID = 0;

int Viewer::init(){
    window = initGL(); 
    if (window == nullptr) { return -1; }
    m_interaction.init(window);

    m_generator.setStartLoc(GridPoint(5, 5));

#ifdef EMSCRIPTEN
    m_programID = LoadStringShaders(std::string(MAZEVERTEXSHADER), std::string(MAZEFRAGMENTSHADER));
#else
    m_programID = LoadShaders( "vertex.glsl", "fragment.glsl");
#endif
    G_MVP_ID = glGetUniformLocation(m_programID, "MVP");
    G_V_ID = glGetUniformLocation(m_programID, "V");
    G_M_ID = glGetUniformLocation(m_programID, "M");
    G_INVTRANSVM_ID = glGetUniformLocation(m_programID, "INVTRANSVM");
    G_ALPHA_ID = glGetUniformLocation(m_programID, "ALPHA");
    m_lightPosID = glGetUniformLocation(m_programID, "LightPosition_world");
    m_last_frame_time = std::chrono::system_clock::now();
    setMVP();
    return 0;
}


void Viewer::loopBody() {
    auto now = std::chrono::system_clock::now();
    if ((now - m_last_frame_time) < std::chrono::milliseconds(100)) {
      return;
    }
    m_last_frame_time = now;
    auto lightPos = m_interaction.cameraLoc();

    // Update the engine state
    m_generator.step();
    m_maze.step();
    
    // Render the scene
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(m_programID);

    auto mvp = P * V * m_interaction.translation() * m_interaction.rotation();
    auto m = glm::mat4(1.0f);
    auto invtransvm = glm::inverse(glm::transpose(V * m));

    glUniformMatrix4fv(G_MVP_ID, 1, GL_FALSE, &mvp[0][0]);
    glUniformMatrix4fv(G_V_ID, 1, GL_FALSE, &V[0][0]);
    glUniformMatrix4fv(G_M_ID, 1, GL_FALSE, &m[0][0]);
    glUniformMatrix4fv(G_INVTRANSVM_ID, 1, GL_FALSE, &invtransvm[0][0]);
    glUniform3f(m_lightPosID, lightPos.x, lightPos.y, lightPos.z);

    //auto mvp = MVP * m_trackball.rotation();
    m_maze.render(mvp, m);

    glfwSwapBuffers(window);
    glfwPollEvents();
};

int Viewer::run(){
    auto frame_start = std::chrono::system_clock::now();
    do {
     loopBody();
      auto sleep_time = (frame_start + std::chrono::milliseconds(100)) - std::chrono::system_clock::now();
      std::this_thread::sleep_for(sleep_time);
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && 
            glfwWindowShouldClose(window) == 0);

    cleanup(m_programID);
    return 0;
}

void Viewer::setMVP() {
    P = glm::perspective(1.04719f, 4.0f/4.0f, 0.1f, 1000.0f);
    V = glm::lookAt(m_interaction.cameraLoc(), glm::vec3(0,0,0), glm::vec3(0,1,0));
    MVP = P * V;
}

void Viewer::cleanup(GLuint programID) {
    glDeleteProgram(programID);
    glfwTerminate();
}
