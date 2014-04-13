#ifndef __SCENE_HPP__
#define __SCENE_HPP__
#include <memory>
#include <vector>

#include <maze/node.hpp>

class Scene {
public:
    void add_node(std::unique_ptr<Node> n) {
        nodes.push_back(std::move(n));
    }

    void print_nodes() {
        for (const auto& n: nodes) {
            n->print();
        }
    }

private:
    std::vector<std::unique_ptr<Node>> nodes;
};

#endif
