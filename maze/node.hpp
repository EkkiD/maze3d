#ifndef __NODE_HPP__
#define __NODE_HPP__
#include<iostream>

static int next_id = 0;
class Node {
public:
    Node():id(next_id){ ++next_id; };

    void print() {
        std::cout<<id<<std::endl;
    }

    virtual void render() {};

private:
    int id;
};

#endif
