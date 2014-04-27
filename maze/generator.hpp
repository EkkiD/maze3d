#ifndef __GENERATOR_HPP__
#define __GENERATOR_HPP__

#include <vector>
#include <maze/common.hpp>

class Maze;

class Generator {
public:
    virtual bool setStartLoc(GridPoint point) = 0;
    virtual bool step() = 0;
};

class DFSGenerator: public Generator {

public:
    DFSGenerator(Maze* maze): m_maze(maze) {}
    virtual bool setStartLoc(GridPoint point);
    virtual bool step();

private:
    Maze* m_maze; // non-owning pointer
    std::vector<GridPoint> m_stack;
};
#endif
