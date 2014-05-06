#ifndef __VIEWER_HPP__
#define __VIEWER_HPP__
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <maze/maze.hpp>
#include <maze/opengl.hpp>
#include <maze/trackball.hpp>

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
    Viewer() : m_trackball(glm::ivec2(1024, 768)), m_mouseDown(false) {};
    int init();
    int run();
    void setMaze(Maze&& s) {
        m_maze = std::move(s);
    }

    Maze * getRawMaze(){
        return &m_maze;
    }
private:
    static void onMouseButton(GLFWwindow* window, int button, int action, int mods);
    static void onMouseMove(GLFWwindow* window, double x, double y);

    void setMVP();
    glm::mat4 MVP;
    glm::mat4 P;
    glm::mat4 V;
    glm::mat4 M;

    void cleanup(GLuint programID);

    Maze m_maze;
    GLFWwindow* window;
    Trackball m_trackball;
    bool m_mouseDown;
};

#endif
