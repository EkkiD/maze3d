#ifndef __CUBE_HPP__
#define __CUBE_HPP__
#include <GL/glew.h>
#include<iostream>
#include <maze/node.hpp>
#include <maze/opengl.hpp>

class Cube: public Node {
public:
    Cube():Node(G_CUBE_VAO){};
};

#endif
