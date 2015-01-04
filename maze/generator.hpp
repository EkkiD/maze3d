#ifndef __GENERATOR_HPP__
#define __GENERATOR_HPP__

#include <vector>
#include <maze/common.hpp>

#include <random>

class Maze;

class Generator {
public:
    virtual void setStartLoc(GridPoint point) = 0;
    virtual bool step() = 0;
};

class DFSGenerator: public Generator {

public:
    DFSGenerator(Maze* maze): m_maze(maze) {
        m_rand.seed(std::random_device()());
    }
    virtual void setStartLoc(GridPoint point);
    virtual bool step();

private:
    bool isAvailable(int row, int col);

    Maze* m_maze; // non-owning pointer
    std::vector<GridPoint> m_stack;
    // Create a random generator
    std::default_random_engine m_rand;
};
#endif
