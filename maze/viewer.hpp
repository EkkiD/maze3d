#ifndef __VIEWER_HPP__
#define __VIEWER_HPP__
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <maze/maze.hpp>
#include <maze/opengl.hpp>
#include <maze/common.hpp>
#include <maze/trackball.hpp>
#include <maze/interaction.hpp>

constexpr static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
};

extern GLuint G_MVP_ID;
extern GLuint G_V_ID;
extern GLuint G_M_ID;

class Viewer {
public:
    Viewer() {};
    int init();
    int run();
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
    glm::mat4 M;

    void cleanup(GLuint programID);

    Maze m_maze;
    GLFWwindow* window;
    Interaction m_interaction;
};

#endif
