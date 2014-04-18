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

    initCube();

    auto scene = Scene();

    auto c = std::unique_ptr<Node>(new Cube());
    scene.add_node(std::move(c));

    scene.print_nodes();
    viewer.setScene(std::move(scene));
    return viewer.run();
}
