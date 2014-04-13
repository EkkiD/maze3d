#include <maze/viewer.hpp>
#include <maze/scene.hpp>
#include <maze/node.hpp>
int main(){
    auto viewer = Viewer();

    auto scene = Scene();
    auto n1 = std::unique_ptr<Node>(new Node());
    auto n2 = std::unique_ptr<Node>(new Node());
    auto n3 = std::unique_ptr<Node>(new Node());
    scene.add_node(std::move(n1));
    scene.add_node(std::move(n2));
    scene.add_node(std::move(n3));
    scene.print_nodes();
    return viewer.run();
}
