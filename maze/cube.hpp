#ifndef __CUBE_HPP__
#define __CUBE_HPP__
#include <GL/glew.h>
#include<iostream>
#include <maze/node.hpp>

class Cube: public Node {
public:
    Cube(GLuint vao):vao(vao){};
    virtual void render();

private:
    GLuint vao;
};

#endif
