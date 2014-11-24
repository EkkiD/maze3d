#include <iostream>
#ifdef EMSCRIPTEN
#include <emscripten/emscripten.h>
#endif
#include <maze/viewer.hpp>
#include <maze/maze.hpp>
#include <maze/node.hpp>
#include <maze/cube.hpp>
#include <maze/generator.hpp>

auto viewer = Viewer();
int main(){

    auto maze = Maze();

    viewer.setMaze(std::move(maze));

    int r = viewer.init();
    if (r < 0) { return -1; }

#ifdef EMSCRIPTEN
    auto bod = []() {viewer.loopBody();};
    emscripten_set_main_loop(bod, 0, 1);
    return 0;
#else
    return viewer.run(); 
#endif
}
