#ifndef __VIEWER_HPP__
#define __VIEWER_HPP__
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <maze/maze.hpp>
#include <maze/opengl.hpp>
#include <maze/common.hpp>
#include <maze/interaction.hpp>
#include <maze/generator.hpp>
#include <chrono>

constexpr static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
};

extern GLuint G_MVP_ID;
extern GLuint G_V_ID;
extern GLuint G_M_ID;
extern GLuint G_ALPHA_ID;

class Viewer {
public:
    Viewer(): m_generator(&m_maze) {};
    int init();
    int run();
    void loopBody();
    void setMaze(Maze&& s) {
        m_maze = std::move(s);
    }

    Maze * getRawMaze(){
        return &m_maze;
    }
private:
    void setMVP();
    glm::mat4 MVP;
    glm::mat4 P;
    glm::mat4 V;

    void cleanup(GLuint programID);

    Maze m_maze;
    GLFWwindow* window;
    Interaction m_interaction;
    DFSGenerator m_generator; 
    GLuint m_programID;
    GLuint m_lightPosID;
    std::chrono::time_point<std::chrono::system_clock> m_last_frame_time;
};

#endif
