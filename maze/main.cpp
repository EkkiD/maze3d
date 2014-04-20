#include <iostream>
#include <maze/viewer.hpp>
#include <maze/scene.hpp>
#include <maze/node.hpp>
#include <maze/cube.hpp>
#include <maze/opengl.hpp>
int main(){
    auto viewer = Viewer();
    int r = viewer.init();
    if (r < 0) { return -1; }

    auto scene = Scene();

    auto c = std::unique_ptr<Node>(new Cube());
    c->scale(0.2f, 0.4f, 0.8f);
    scene.add_node(std::move(c));

    auto c2 = std::unique_ptr<Node>(new Cube());
    c2->translate(-1.0f, -1.0f, -1.0f);
    scene.add_node(std::move(c2));

    scene.print_nodes();
    viewer.setScene(std::move(scene));
    return viewer.run();
}
