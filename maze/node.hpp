#ifndef __NODE_HPP__
#define __NODE_HPP__
#include <GL/glew.h>
#include<iostream>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

static int next_id = 0;
class Node {
public:
    Node(GLuint vao): m_vao(vao), id(next_id), m_transform(glm::mat4())
    { 
      ++next_id; 
    };

    void print() {
        std::cout<<id<<std::endl;
    };

    void render(glm::mat4 MVP);

    void translate(float x, float y, float z);

    void scale(float x, float y, float z);
private:
    GLuint m_vao;
    int id;

    glm::mat4 m_transform;
};

#endif
