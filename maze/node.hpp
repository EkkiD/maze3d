#ifndef __NODE_HPP__
#define __NODE_HPP__
#include <GL/glew.h>
#include<iostream>

static int next_id = 0;
class Node {
public:
    Node(GLuint vao):m_vao(vao),id(next_id){ ++next_id; };

    void print() {
        std::cout<<id<<std::endl;
    };

    void render();

private:
    GLuint m_vao;
    int id;
};

#endif
