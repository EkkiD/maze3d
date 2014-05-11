#include <iostream>
#include <maze/viewer.hpp>
#include <maze/maze.hpp>
#include <maze/node.hpp>
#include <maze/cube.hpp>
#include <maze/generator.hpp>

int main(){
    auto viewer = Viewer();

    auto maze = Maze();

    viewer.setMaze(std::move(maze));

    int r = viewer.init();
    if (r < 0) { return -1; }

    return viewer.run();
}
