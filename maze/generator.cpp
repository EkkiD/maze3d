#include <maze/generator.hpp>
#include <maze/maze.hpp>
#include <maze/common.hpp>

#include <stdlib.h>  //rand()


void DFSGenerator::setStartLoc(GridPoint point) {
    m_stack.push_back(point);
}

bool DFSGenerator::isAvailable(int row, int col) {
    if ((row < 0) || (row >= NUM_ROWS)) { return false; }
    if ((col < 0) || (col >= NUM_COLS)) { return false; }
    return m_maze->getCell(row, col)->isUntouched();
}

bool DFSGenerator::step() {
    if (m_stack.empty()) {
        return false;
    }

    auto top = m_stack.back();
    m_stack.pop_back();
    int row = top.x;
    int col = top.y;

    auto* cell = m_maze->getCell(row, col);

    cell->setStatus(VISITED);
    std::vector<unsigned char> neighbours;

    if (cell->isStanding(NORTH) && isAvailable(row-1, col)) {
        neighbours.push_back(NORTH);
    }
    if (cell->isStanding(SOUTH) && isAvailable(row+1, col)) {
        neighbours.push_back(SOUTH);
    }
    if (cell->isStanding(WEST) && isAvailable(row, col-1)) {
        neighbours.push_back(WEST);
    }
    if (cell->isStanding(EAST) && isAvailable(row, col+1)) {
        neighbours.push_back(EAST);
    }


    // no neighbours => pop stack
    if (neighbours.empty()) {
        if (m_stack.empty()) {
            return false;
        }

        top = m_stack.back();
        row = top.x;
        col = top.y;
        m_maze->getCell(row, col)->setStatus(CURRENT);
        return true;
    }

    int index = rand() % neighbours.size();
    int direction = neighbours[index];
    auto new_loc = GridPoint(0, 0);
    
    if (direction & NORTH) {
        m_maze->getCell(row -1, col)->tearDown(SOUTH, direction);
        cell->tearDown(NORTH, direction);
        new_loc = GridPoint(row-1, col);
    } 
    if (direction & SOUTH) {
        m_maze->getCell(row +1, col)->tearDown(NORTH, direction);
        cell->tearDown(SOUTH, direction);
        new_loc = GridPoint(row+1, col);
    } 
    if (direction & EAST) {
        m_maze->getCell(row, col+1)->tearDown(WEST, direction);
        cell->tearDown(EAST, direction);
        new_loc = GridPoint(row, col+1);
    } 
    if (direction & WEST) {
        m_maze->getCell(row, col-1)->tearDown(EAST, direction);
        cell->tearDown(WEST, direction);
        new_loc = GridPoint(row, col-1);
    } 


    cell->setStatus(STACKED);
    m_stack.push_back(top);
    m_stack.push_back(new_loc);
    m_maze->getCell(new_loc.x, new_loc.y)->setStatus(CURRENT);

    return true;
}
