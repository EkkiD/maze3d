#ifndef __VIEWER_HPP__
#define __VIEWER_HPP__
#include <test/opengl.hpp>
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

constexpr static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
};

class Viewer {
public:
    int run();
private:
        
    GLuint setupVertexArray();

    glm::mat4 getMVP();

    GLuint setupVertexBuffer(const GLuint shaderAttr);

    void cleanup(GLuint vertexbuffer, GLuint programID, GLuint vertexarray);

};

#endif
