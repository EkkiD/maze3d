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

    void render(glm::mat4 MVP, glm::mat4 M) const;

    void tearDown(int direction);

    void setStatus(STATUS stat) { m_status = stat; }

    STATUS getStatus() { return m_status; }

    bool isUntouched() { return m_status == UNTOUCHED; }

    bool isStanding(unsigned char direction) {
        return (m_wall_bitmask & direction) != 0 ;
    }

private:
    unsigned char m_wall_bitmask;
    int m_row;
    int m_col;
    Wall n_wall;
    Wall w_wall;
    STATUS m_status;
};

class Maze {
public:

    Maze(); 

    void add_node(std::unique_ptr<Node> n) {
        nodes.push_back(std::move(n));
    }

    void print_nodes() const {
        for (const auto& n: nodes) {
            n->print();
        }
    }

    void render(glm::mat4 MVP, glm::mat4 M) const {
        for (const auto& n: nodes) {
            n->render(MVP);
        }

        for (const auto& c: m_cells) {
            c.render(MVP, M);
        }

        for (const auto& side_wall: m_side_walls) {
            side_wall.render(MVP, M);
        }
    }

    void tearDown(int row, int col, bool north);

    Cell* getCell(int row, int col) {
        int index = row * NUM_COLS + col; 
        return &(m_cells[index]);
    }

private:
    std::vector<std::unique_ptr<Node>> nodes;
    std::vector<Cell> m_cells;
    std::vector<Wall> m_side_walls;
};

#endif
