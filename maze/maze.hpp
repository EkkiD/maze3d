#ifndef __MAZE_HPP__
#define __MAZE_HPP__
#include <memory>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <maze/node.hpp>
#include <maze/wall.hpp>

#include <maze/common.hpp>

class Cell {
public:
    Cell(int row, int col);

    void render(glm::mat4 MVP, glm::mat4 M, glm::mat4 V, glm::mat4 invtransvm) const;

    void tearDown(int direction, int fall_direction);

    void setStatus(STATUS stat) { m_status = stat; }

    STATUS getStatus() { return m_status; }

    bool isUntouched() { return m_status == UNTOUCHED; }

    bool isStanding(unsigned char direction) {
        return (m_wall_bitmask & direction) != 0 ;
    }

    void step() {
        n_wall.step();
        w_wall.step();
    }

private:
    unsigned char m_wall_bitmask;
    int m_row;
    int m_col;
    Wall n_wall;
    Wall w_wall;
    STATUS m_status = UNTOUCHED;
};

class Maze {
public:

    Maze(); 

    void step() {
        for (auto& c: m_cells) {
            c.step();
        }
    }

    void render(glm::mat4 MVP, glm::mat4 M, glm::mat4 V, glm::mat4 invtransvm) const {
        for (const auto& c: m_cells) {
            c.render(MVP, M, V, invtransvm);
        }

        for (const auto& side_wall: m_side_walls) {
            side_wall.render(MVP, M, V, invtransvm);
        }
    }

    Cell* getCell(int row, int col) {
        int index = row * NUM_COLS + col; 
        return &(m_cells[index]);
    }

private:
    std::vector<Cell> m_cells;
    std::vector<Wall> m_side_walls;
};

#endif
