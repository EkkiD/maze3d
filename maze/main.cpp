#include <iostream>
#include <maze/viewer.hpp>
#include <maze/maze.hpp>
#include <maze/node.hpp>
#include <maze/cube.hpp>
#include <maze/generator.hpp>

int main(){
    auto viewer = Viewer();
    int r = viewer.init();
    if (r < 0) { return -1; }

    auto maze = Maze();

    maze.print_nodes();

    viewer.setMaze(std::move(maze));

    auto generator = DFSGenerator(viewer.getRawMaze());

    generator.setStartLoc(GridPoint(5, 5));
    while (generator.step()) {
    }
    return viewer.run();
}
