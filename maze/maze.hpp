#ifndef __MAZE_HPP__
#define __MAZE_HPP__
#include <memory>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <maze/node.hpp>
#include <maze/wall.hpp>

class Cell {
public:
    Cell(int row, int col);

    void render(glm::mat4 MVP, glm::mat4 M) const;

private:
    char m_wall_bitmask;
    int m_row;
    int m_col;
    Wall n_wall;
    Wall w_wall;
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

        for (const auto c: m_cells) {
            c.render(MVP, M);
        }
    }

private:
    static int const NUM_ROWS = 10;
    static int const NUM_COLS = 10;
    std::vector<std::unique_ptr<Node>> nodes;
    std::vector<Cell> m_cells;
};

#endif
