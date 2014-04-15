#include <maze/viewer.hpp>
#include <maze/scene.hpp>
#include <maze/node.hpp>
#include <maze/cube.hpp>
#include <maze/opengl.hpp>
int main(){
    auto viewer = Viewer();
    int r = viewer.init();
    if (r < 0) { return -1; }

    auto vao = initCube();

    auto scene = Scene();
    auto n1 = std::unique_ptr<Node>(new Node());
    auto n2 = std::unique_ptr<Node>(new Node());
    auto n3 = std::unique_ptr<Node>(new Node());

    auto c = std::unique_ptr<Node>(new Cube(vao));

    scene.add_node(std::move(n1));
    scene.add_node(std::move(n2));
    scene.add_node(std::move(n3));
    scene.add_node(std::move(c));

    scene.print_nodes();
    viewer.setScene(std::move(scene));
    return viewer.run();
}
