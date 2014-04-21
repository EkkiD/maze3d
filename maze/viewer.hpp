#ifndef __VIEWER_HPP__
#define __VIEWER_HPP__
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <maze/maze.hpp>
#include <maze/opengl.hpp>

constexpr static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
};

extern GLuint G_MVP_ID;

class Viewer {
public:
    int init();
    int run();
    void setMaze(Maze s) {
        m_maze = std::move(s);
    }
private:

    glm::mat4 getMVP();

    void cleanup(GLuint programID);

    Maze m_maze;
    GLFWwindow* window;
};

#endif
