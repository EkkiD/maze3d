#ifndef __VIEWER_HPP__
#define __VIEWER_HPP__
#include <maze/opengl.hpp>
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <maze/scene.hpp>

constexpr static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
};

class Viewer {
public:
    int init();
    int run();
    void setScene(Scene s) {
        scene = std::move(s);
    }
private:

    glm::mat4 getMVP();

    void cleanup(GLuint programID);

    Scene scene;
    GLFWwindow* window;
};

#endif
