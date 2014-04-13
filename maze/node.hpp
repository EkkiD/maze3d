#ifndef __NODE_HPP__
#define __NODE_HPP__
#include<iostream>

class Node {
public:
    Node():id(next_id){ ++next_id; };

    void print() {
        std::cout<<id<<std::endl;
    }

private:
    static int next_id;
    int id;
};
int Node::next_id = 0;

#endif
