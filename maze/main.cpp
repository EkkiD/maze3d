#include <iostream>
#include <maze/viewer.hpp>
#include <maze/maze.hpp>
#include <maze/node.hpp>
#include <maze/cube.hpp>
#include <maze/opengl.hpp>
int main(){
    auto viewer = Viewer();
    int r = viewer.init();
    if (r < 0) { return -1; }

    auto maze = Maze();

    auto c = std::unique_ptr<Node>(new Cube());
    c->scale(0.2f, 0.4f, 0.8f);
    maze.add_node(std::move(c));

    auto c2 = std::unique_ptr<Node>(new Cube());
    c2->translate(-1.0f, -1.0f, -1.0f);
    maze.add_node(std::move(c2));

    maze.print_nodes();
    viewer.setMaze(std::move(maze));
    return viewer.run();
}
