#ifndef __MAZE_HPP__
#define __MAZE_HPP__
#include <memory>
#include <vector>
#include <maze/node.hpp>

class Cell {
public:


};

class Maze {
public:
    void add_node(std::unique_ptr<Node> n) {
        nodes.push_back(std::move(n));
    }

    void print_nodes() {
        for (const auto& n: nodes) {
            n->print();
        }
    }

    void render(glm::mat4 MVP) {
        for (const auto& n: nodes) {
            n->render(MVP);
        }
    }

private:
    std::vector<std::unique_ptr<Node>> nodes;
};

#endif
